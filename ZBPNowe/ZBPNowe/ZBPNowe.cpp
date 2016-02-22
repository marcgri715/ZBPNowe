// ZBPNowe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tree.h"
#include <string>
#include "ILeafIterator.h"
#include "Timer.h"
#include <fstream>
#include <sstream>


int main()
{
    //std::string* string = new std::string("abracadabra");
    //std::string* string = new std::string("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    printf("Podaj liczbê znaków do za³adowania (powy¿ej 10000): ");
    int limit;
    scanf_s("%d", &limit);
    std::fstream file;
    file.open("bigTextFile.txt");
    std::stringstream strStream;
    strStream << file.rdbuf();
    file.close();
    std::ofstream toWrite;
    std::stringstream result;
    std::string* toFind = nullptr;
    std::stringstream filename;
    filename << "results" << limit << ".txt";
    toWrite.open(filename.str(), std::ios::app);
    srand(time(NULL));
    std::string* string = new std::string(strStream.str().substr(0, limit - 1));
    string->push_back(0);
    double durationSummed = 0.0;
    std::shared_ptr<CTree> tree(new CTree());
    tree->LoadString(string);
    CTimer timer;
    timer.StartTimer();
    tree->CreateTree();
    durationSummed = timer.CheckTimer();
    result << durationSummed;
    durationSummed = 0.0;
    for (int k = 1; k <= 10; k++) {
        for (int j = 0; j < 100; j++) {
            if (toFind) delete toFind;
            toFind = new std::string(string->substr(rand() % (limit - k * 1000), k * 1000));
            timer.StartTimer();
            tree->FindPhrase(toFind);
            durationSummed += timer.CheckTimer();
        }
        result << '\t' << durationSummed / 100.0;
    }
    result << '\n';
    toWrite.write(result.str().c_str(), result.str().size());
    toWrite.flush();
    delete string;
    toWrite.close();
    printf("koniec dzialania programu");
    delete toFind;
}

