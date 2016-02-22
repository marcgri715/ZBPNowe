#pragma once
#include "Node.h"
#include "Tree.h"

class IChildIterator
{
public:
    IChildIterator() { currentNode = last = parentNode = nullptr; }
    IChildIterator(std::shared_ptr<TNode> x, bool includeRoot = false);
    IChildIterator(const IChildIterator& iter) : currentNode(iter.currentNode), last(iter.last), parentNode(iter.parentNode) {}
    ~IChildIterator() { currentNode = nullptr; last = nullptr; parentNode = nullptr; }
    IChildIterator& operator++();
    IChildIterator operator++(int);
    bool IsLast();
    std::shared_ptr<TNode>& operator*() { return currentNode; }
    IChildIterator& operator=(IChildIterator iter) { currentNode = iter.currentNode; last = iter.last; parentNode = iter.parentNode; return *this; }

private:
    std::shared_ptr<TNode> currentNode;
    std::shared_ptr<TNode> last;
    std::shared_ptr<TNode> parentNode;
};