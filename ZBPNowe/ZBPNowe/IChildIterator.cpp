#include "stdafx.h"
#include "IChildIterator.h"


IChildIterator::IChildIterator(std::shared_ptr<TNode> x, bool includeRoot)
{
    if (!includeRoot) {
        currentNode = x->children.front();
        last = x->children.back();
        parentNode = x;
    } else {
        currentNode = last = x;
        parentNode = nullptr;
    }
}

IChildIterator & IChildIterator::operator++()
{
    if (currentNode != last) {
        int index = 0;
        for each (std::shared_ptr<TNode> child in parentNode->children) {
            if (currentNode == child)
                break;
            index++;
        }
        currentNode = parentNode->children.at(index + 1);
    }
    return *this;
}

IChildIterator IChildIterator::operator++(int)
{
    IChildIterator result(*this);
    ++(*this);
    return result;
}

bool IChildIterator::IsLast()
{
    return currentNode == last;
}