#include "stdafx.h"
#include "Tree.h"


CTree::CTree()
{
    std::shared_ptr<TNode> nowy = std::make_shared<TNode>(-1, -1);
    root = activeNode = nowy;
    activeEdge = activeLength = 0;
    lastAddedNode = nowy;
    position = -1;
    remainder = 0;
    count = 0;
    string = nullptr;
}


CTree::~CTree()
{
    if (string) {
        delete string;
    }
    std::vector<IChildIterator> iterstack;
    iterstack.resize(0);
    IChildIterator child(root, true);
    while (true) {
        if (0 == (*child)->children.size()) {
            if (iterstack.size() == 0)
                break;
            child = iterstack.back();
            iterstack.pop_back();
            (*child)->children.erase((*child)->children.begin());
            child++;
            continue;
        }
        if ((*child)->children.front()->indexEnd != INF) {
            iterstack.push_back(child);
            child = IChildIterator(*child);
            continue;
        }
        std::shared_ptr<TNode> temp = (*child)->children.front();
        if (temp->suffixLink) temp->suffixLink = nullptr;
        (*child)->children.erase((*child)->children.begin());
    }
    
    OutputDebugString(L"tree dies\n");
}

void CTree::LoadString(std::string* newString)
{
    if (string) delete string;
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
    while (true) {
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
        if (child.IsLast()) break;
        child++;
    }
    return false;
}

void CTree::PrintSuffix(std::vector<long> indexes)
{
    std::string toBePrinted;
    for (int i = 0; i < indexes.size(); i += 2) {
        toBePrinted.append(*string, indexes.at(i), indexes.at(i + 1));
    }
    printf("Suffix: %s\n", toBePrinted.c_str());
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
            std::shared_ptr<TNode> newLeaf = std::make_shared<TNode>(position, count++);
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
            if (selected->children.size() > 0) {
                long lastStart = selected->indexStart;
                selected->indexStart = selected->indexStart + activeLength;
                std::shared_ptr<TNode> newNode = std::make_shared<TNode>(lastStart, count++);
                newNode->indexEnd = selected->indexStart;
                newNode->children.push_back(selected);
                std::shared_ptr<TNode> yetAnotherNewLeaf = std::make_shared<TNode>(position, count++);
                newNode->children.push_back(yetAnotherNewLeaf);
                std::vector<std::shared_ptr<TNode>>::iterator iter;
                iter = activeNode->children.begin();
                while (true) {
                    if (*iter == selected) {
                        activeNode->children.insert(iter, newNode);
                        iter = activeNode->children.begin();
                        while (true) {
                            if (*iter == selected) {
                                activeNode->children.erase(iter);
                                break;
                            }
                            iter++;
                        }
                        break;
                    }
                    iter++;
                }
                AddSuffixLink(newNode);
            }
            else {
                selected->indexEnd = selected->indexStart + activeLength;
                std::shared_ptr<TNode> newLeaf = std::make_shared<TNode>(selected->indexEnd, count++);
                selected->children.push_back(newLeaf);
                std::shared_ptr<TNode> yetAnotherNewLeaf = std::make_shared<TNode>(position, count++);
                selected->children.push_back(yetAnotherNewLeaf);
                AddSuffixLink(selected);
            }
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
