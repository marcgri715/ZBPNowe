// ZBPNowe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tree.h"
#include <string>


int main()
{
    //std::string* string = new std::string("abracadabra");
    std::string* string = new std::string("abcabx");
    string->push_back(0);
    std::shared_ptr<CTree> tree(new CTree());
    tree->LoadString(string);
    tree->CreateTree();
    printf("UDALO SIE?!");
    getchar();
    if (string) delete string;
    _CrtDumpMemoryLeaks();
}

