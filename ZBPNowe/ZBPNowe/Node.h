#pragma once
#include <algorithm>
#include <vector>
#include <memory>
#include <Windows.h>

#define INF 1<<30

struct TNode : public std::enable_shared_from_this<TNode>{
    long int indexStart;
    long int indexEnd;
    std::vector<std::shared_ptr<TNode>> children;
    std::shared_ptr<TNode> suffixLink;
    int count;
    TNode(long int pIndexStart, int pCount) {
        indexStart = pIndexStart;
        indexEnd = INF;
        children.clear();
        suffixLink = nullptr;
        count = pCount;
    }
    ~TNode() {
        //OutputDebugString(L"node dies\n");
    }
    int EdgeLength(long int pos) {
        return min(indexEnd, pos+1) - indexStart;
    }
};

