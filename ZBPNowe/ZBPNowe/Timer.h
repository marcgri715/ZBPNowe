#pragma once
#include <chrono>
#include <ctime>

class CTimer
{
public:
    CTimer();
    ~CTimer();
    void StartTimer();
    double CheckTimer();
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};

