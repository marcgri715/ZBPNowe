#pragma once
#include <algorithm>
#include <vector>
#include <memory>

#define INF 1<<30

struct TNode : public std::enable_shared_from_this<TNode>{
    long int indexStart;
    long int indexEnd;
    std::vector<std::shared_ptr<TNode>> children;
    std::shared_ptr<TNode> suffixLink;
    TNode(long int pIndexStart) {
        indexStart = pIndexStart;
        indexEnd = INF;
        children.clear();
        suffixLink = nullptr;
    }
    int EdgeLength(long int pos) {
        return std::min(indexEnd, pos+1) - indexStart;
    }
};

