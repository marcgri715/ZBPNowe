#pragma once
#include <iterator>
#include "Node.h"
#include <memory>

class ILeafIterator : public std::iterator<std::input_iterator_tag, TNode> {
public:
    ILeafIterator(std::shared_ptr<TNode> x);
    ILeafIterator(const ILeafIterator& iter) : currentNode(iter.currentNode), last(iter.last) {}
    ILeafIterator& operator++();
    ILeafIterator operator++(int);
    bool IsLast();
    std::shared_ptr<TNode>& operator*() { return currentNode; }

private:
    std::shared_ptr<TNode> currentNode;
    std::shared_ptr<TNode> last;
};