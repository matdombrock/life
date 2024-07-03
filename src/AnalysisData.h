#pragma once
#include <vector>
struct AnalysisData 
{
    std::vector<double> birthsVec;
    std::vector<double> deathsVec;
    std::vector<double> aliveVec;
    std::vector<double> ageVec;
    std::vector<double> peakAgeVec;
    std::vector<double> neighborsVec;
    int generationsCount = 0;
    int peakAge = 0;
    double avgAge = 0;
    double avgNeighbors = 0;
    double avgBirths = 0;
    double avgDeaths = 0;
    int finalAlive = 0;
    int births = 0;
    int deaths = 0;
    int frozen = 0;
    bool popDeath = 0;
};