#pragma once
#include <algorithm>
#include <list>

struct TNode : public std::enable_shared_from_this<TNode>{
    long int indexStart;
    long int indexEnd;
    std::list<std::shared_ptr<TNode>> children;
    std::shared_ptr<TNode> suffixLink;
    char firstLetter;
    TNode(long int pIndexStart, char pFirstLetter) {
        indexStart = pIndexStart;
        indexEnd = 1 << 30;
        children.clear();
        suffixLink = nullptr;
        firstLetter = pFirstLetter;
    }
    int EdgeLength(long int pos) {
        return std::min(indexEnd, pos+1) - indexStart;
    }
};

