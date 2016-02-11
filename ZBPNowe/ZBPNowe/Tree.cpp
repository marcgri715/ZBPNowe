#include "stdafx.h"
#include "Tree.h"


CTree::CTree()
{
    std::shared_ptr<TNode> nowy(new TNode(-1));
    root = activeNode = nowy;
    activeEdge = activeLength = 0;
    lastAddedNode = nowy;
    position = -1;
    remainder = 0;
}


CTree::~CTree()
{
    if (string) {
        delete string;
    }
    std::vector<IChildIterator> iterstack;
    std::vector<int> indexstack;
    iterstack.clear();
    IChildIterator child(root, true);
    int index = 0;
    while (true) {
        if (index == (*child)->children.size()) {
            child = iterstack.back();
            iterstack.pop_back();
            index = indexstack.back();
            indexstack.pop_back();
            std::shared_ptr<TNode> temp = (*child);
            child++;
            index++;
            continue;
        }
        if ((*child)->children.at(index)->indexEnd != INF) {
            iterstack.push_back(child);
            indexstack.push_back(index);
            child = IChildIterator(*child);
            index = 0;
            continue;
        }
        std::shared_ptr<TNode> temp = (*child)->children.at(index);
        //child++;
        if (temp->suffixLink) temp->suffixLink = nullptr;
        index++;
    }
    iterstack.clear();
    indexstack.clear();
}

void CTree::LoadString(std::string* newString)
{
    string = new std::string(*newString);
}

void CTree::CreateTree()
{
    for (int i = 0; i < string->size(); i++) {
        ExtendTree();
    }
}

bool CTree::FindPhrase(std::string * toFind)
{
    int index = 0;
    IChildIterator child(root);
    do {
        if (string->at((*child)->indexStart) == toFind->at(index)) {
            index++;
            if (index == toFind->size() - 1)
                return true;
            bool missed = false;
            for (int i = 1; i < (*child)->indexEnd - (*child)->indexStart; i++) {
                if (string->at((*child)->indexStart + i) == 0)
                    return false;
                //string is too long
                if (string->at((*child)->indexStart + i) != toFind->at(index++)) {
                    missed = true;
                    break;
                }
                //character missed;
                if (index == toFind->size() - 1)
                    return true;
            }
            if (missed)
                break;
            child = IChildIterator(*child);
            continue;
        }
        child++;
    } while (!child.IsLast());
    return false;
}

void CTree::PrintSuffix(std::vector<long> indexes)
{
    std::string toBePrinted;
    for (int i = 0; i < indexes.size(); i += 2) {
        toBePrinted.append(*string, indexes.at(i), indexes.at(i + 1));
    }
    printf("Suffix: %s", toBePrinted.c_str());
}

void CTree::PrintTree()
{
    PrintTree(root, 0, 0);
}

std::shared_ptr<TNode> CTree::GetRoot()
{
    return root;
}

void CTree::AddSuffixLink(std::shared_ptr<TNode> node)
{
    if (lastAddedNode) lastAddedNode->suffixLink = node;
    lastAddedNode = node->shared_from_this();
}

bool CTree::WalkDown(std::shared_ptr<TNode> node)
{
    if (activeLength >= node->EdgeLength(position)) {
        activeEdge += node->EdgeLength(position);
        activeLength -= node->EdgeLength(position);
        activeNode = node;
        return true;
    }
    return false;
}

void CTree::ExtendTree()
{
    ++position;
    lastAddedNode = nullptr;
    remainder++;
    while (remainder > 0) {
        if (activeLength == 0) activeEdge = position;
        std::shared_ptr<TNode> selected = nullptr;
        for each (std::shared_ptr<TNode> child in activeNode->children) {
            if (string->at(child->indexStart) == GetActiveEdge()) {
                selected = child;
                break;
            }
        }
        if (!selected) {
            std::shared_ptr<TNode> newLeaf(new TNode(position));
            activeNode->children.push_back(newLeaf);
            AddSuffixLink(activeNode);
        }
        else {
            if (WalkDown(selected)) continue;
            if (string->at(selected->indexStart + activeLength) == string->at(position)) {
                activeLength++;
                AddSuffixLink(activeNode);
                break;
            }
            //split
            long lastEnd = selected->indexEnd;
            selected->indexEnd = selected->indexStart + activeLength;
            std::shared_ptr<TNode> newLeaf(new TNode(selected->indexEnd));
            if (selected->children.size() > 0) {
                newLeaf->children = selected->children;
                newLeaf->indexEnd = lastEnd;
                selected->children.clear();
            }
            selected->children.push_back(newLeaf);
            std::shared_ptr<TNode> yetAnotherNewLeaf(new TNode(position));
            selected->children.push_back(yetAnotherNewLeaf);
            AddSuffixLink(selected);
        }
        remainder--;
        if (activeNode == root && activeLength > 0) {
            activeLength--;
            activeEdge = position - remainder + 1;
        }
        else {
            if (activeNode->suffixLink) {
                activeNode = activeNode->suffixLink;
            }
            else {
                activeNode = root;
            }
        }
    }
}

char CTree::GetActiveEdge()
{
    return string->at(activeEdge);
}

void CTree::PrintTree(std::shared_ptr<TNode> node, int level, int emptySpaces)
{
    IChildIterator iterator(node);
    do {
        for (int i = 0; i < level; i++) {
            printf("   ");
        }
        for (int i = 0; i < emptySpaces; i++) {
            printf(" ");
        }
        printf(" -");
        long limit = std::min((*iterator)->indexEnd, (long)string->size());
        for (int i = (*iterator)->indexStart; i < limit; i++) {
            printf("%c", string->at(i));
        }
        printf("-|\n");
        for (int i = 0; i < level; i++) {
            printf("   ");
        }
        for (int i = 0; i < emptySpaces; i++) {
            printf(" ");
        }
        int letters = limit - (*iterator)->indexStart;
        for (int i = 0; i < letters; i++) {
            printf(" ");
        }
        letters = letters;
        printf("   |\n");
        if ((*iterator)->children.size() > 0) {
            PrintTree((*iterator), level+1, emptySpaces + letters);
        }
        if (iterator.IsLast()) {
            break;
        }
        iterator++;
    } while (true);
}
