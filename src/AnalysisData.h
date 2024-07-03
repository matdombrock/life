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
    int generationsCount;
    int peakAge;
    double avgAge;
    double avgNeighbors;
    double avgBirths;
    double avgDeaths;
    int finalAlive;
    int births;
    int deaths;
    int frozen;
    bool popDeath;
};