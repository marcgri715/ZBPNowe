#pragma once
#include <iterator>
#include "Node.h"
#include <memory>

class ILeafIterator : public std::iterator<std::input_iterator_tag, TNode> {
public:
    ILeafIterator(std::shared_ptr<TNode> x);
    ILeafIterator(const ILeafIterator& iter) : currentNode(iter.currentNode), last(iter.last), parentStack(iter.parentStack) {}
    ~ILeafIterator() { currentNode = nullptr; last = nullptr; for each(std::shared_ptr<TNode> child in parentStack) child = nullptr; parentStack.clear(); }
    ILeafIterator& operator++();
    ILeafIterator operator++(int);
    ILeafIterator& operator=(ILeafIterator iter) { currentNode = iter.currentNode; last = iter.last; parentStack = iter.parentStack; return *this; }
    bool IsLast();
    std::vector<long> operator*();

private:
    std::shared_ptr<TNode> currentNode;
    std::shared_ptr<TNode> last;
    std::vector<std::shared_ptr<TNode>> parentStack;
};