// ZBPNowe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tree.h"
#include <string>
#include "ILeafIterator.h"


int main()
{
    std::string* string = new std::string("abracadabraabracadabraabracadabra");
    //std::string* string = new std::string("abracadabraabracadabra");
    //std::string* string = new std::string("abcabxabcd");
    //std::string* string = new std::string("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    //std::string* string = new std::string("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ");
    string->push_back(0);
    std::shared_ptr<CTree> tree(new CTree());
    tree->LoadString(string);
    tree->CreateTree();
    ILeafIterator iterator(tree->GetRoot());
    int i = 0;
    do {
        std::vector<long> indexes = *iterator;
        tree->PrintSuffix(indexes);
        i++;
        if (iterator.IsLast()) {
            break;
        }
        iterator++;
    } while (true);
    std::string* toFind = new std::string("aabrac");
    printf("%d - %d", string->size(), i);
    if (tree->FindPhrase(toFind)) {
        printf("\nznaleziono!");
    }
    else {
        printf("\nnie znaleziono!");
    }
    //system("CLS");
    //tree->PrintTree();
    getchar();
    if (string) delete string;
    delete toFind;
    _CrtDumpMemoryLeaks();
}

