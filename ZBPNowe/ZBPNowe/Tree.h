#pragma once
#include <memory>
#include <vector>
#include "Node.h"

class CTree
{
public:
    CTree();
    ~CTree();
    void LoadString(std::string* newString);
    void CreateTree();
private:
    std::shared_ptr<TNode>  root;
    std::shared_ptr<TNode>  activeNode;
    long int                activeEdge;
    long int                activeLength;
    std::string*            string;
    std::shared_ptr<TNode>  lastAddedNode;
    long int                position;
    long int                remainder;

    void AddSuffixLink(std::shared_ptr<TNode> node);
    bool WalkDown(std::shared_ptr<TNode> node);
    void ExtendTree();
    char GetActiveEdge();
};

