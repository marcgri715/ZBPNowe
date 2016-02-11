#include "stdafx.h"
#include "ILeafIterator.h"



ILeafIterator::ILeafIterator(std::shared_ptr<TNode> x)
{
    std::shared_ptr<TNode> temp = x;
    parentStack.push_back(temp);
    while (true) {
        if (temp->children.front()->indexEnd == INF) {
            currentNode = temp->children.front();
            break;
        }
        temp = temp->children.front();
        parentStack.push_back(temp);
    }
    temp = x;
    while (true) {
        if (temp->children.back()->indexEnd == INF) {
            last = temp->children.back();
            break;
        }
        temp = temp->children.back();
    }
}

ILeafIterator& ILeafIterator::operator++()
{
    if (currentNode != last) {
        while (true) {
            std::shared_ptr<TNode> tempNode = parentStack.back();
            int index = 0;
            for each (std::shared_ptr<TNode> child in tempNode->children) {
                if (child == currentNode)
                    break;
                index++;
            }
            if (index >= tempNode->children.size() - 1) {
                currentNode = tempNode;
                parentStack.pop_back();
                continue;
            }
            if (tempNode->children[++index]->indexEnd == INF) {
                currentNode = tempNode->children[index];
                break;
            }
            tempNode = tempNode->children[index];
            while (true) {
                if (tempNode->children.front()->indexEnd == INF) {
                    currentNode = tempNode->children.front();
                    break;
                }
                parentStack.push_back(tempNode);
                tempNode = tempNode->children.front();
            }
            break;
        }
    }
    return *this;
}

ILeafIterator ILeafIterator::operator++(int) {
    ILeafIterator result(*this);
    ++(*this);
    return result;
}

bool ILeafIterator::IsLast()
{
    return currentNode == last;
}

std::vector<long> ILeafIterator::operator*()
{
    std::vector<long> indexes;
    for (int i = 1; i < parentStack.size(); i++) {
        indexes.push_back(parentStack.at(i)->indexStart);
        indexes.push_back(parentStack.at(i)->indexEnd - parentStack.at(i)->indexStart);
    }
    indexes.push_back(currentNode->indexStart);
    indexes.push_back(currentNode->indexEnd - currentNode->indexStart);
    return indexes;
}
