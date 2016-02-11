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
    std::shared_ptr<TNode> parent;
    TNode(long int pIndexStart, std::shared_ptr<TNode> pParent) {
        indexStart = pIndexStart;
        indexEnd = INF;
        children.clear();
        suffixLink = nullptr;
        parent = pParent;
    }
    int EdgeLength(long int pos) {
        return std::min(indexEnd, pos+1) - indexStart;
    }
};

