#pragma once
#include <memory>
#include <vector>
#include "IChildIterator.h"
#include "Node.h"

class CTree
{
public:
    CTree();
    ~CTree();
    CTree(const CTree&) = delete;
    CTree& operator = (const CTree&) = delete;
    void LoadString(std::string* newString);
    void CreateTree();
    bool FindPhrase(std::string* toFind);
    void PrintSuffix(std::vector<long> indexes);
    std::shared_ptr<TNode> GetRoot();

private:
    std::shared_ptr<TNode>  root;
    std::shared_ptr<TNode>  activeNode;
    long int                activeEdge;
    long int                activeLength;
    std::string*            string;
    std::shared_ptr<TNode>  lastAddedNode;
    long int                position;
    long int                remainder;
    int                     count;

    void AddSuffixLink(std::shared_ptr<TNode> node);
    bool WalkDown(std::shared_ptr<TNode> node);
    void ExtendTree();
    char GetActiveEdge();
};

