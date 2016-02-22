#include "stdafx.h"
#include "Timer.h"


CTimer::CTimer()
{
}


CTimer::~CTimer()
{
}

void CTimer::StartTimer()
{
    start = std::chrono::high_resolution_clock::now();
}

double CTimer::CheckTimer()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> check = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedSeconds = check - start;
    double endTime = elapsedSeconds.count();
    return endTime;
}
