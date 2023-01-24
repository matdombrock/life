#pragma once
#include <vector>
#include <string>
#include "util/MathTools.h"
#include "util/StringTools.h"
#include "util/FileIO.h"
class GenerationAnalysis
{
public:
    void analyzeCell(int neighbors, int age, bool died, bool born, bool alive){
        neighborsVec.push_back(neighbors);
        ageVec.push_back(age);
    }
    void death()
    {
        deaths++;
    }
    void birth()
    {
        births++;
    }
    void alive()
    {
        living++;
    }
    void setNeighbors(int count)
    {
        neighborsVec.push_back(count);
    }
    void setAge(int count)
    {
        ageVec.push_back(count);
    }
    void finalize()
    {
        avgNeighbors = MathTools::avgVec(neighborsVec);
        avgAge = MathTools::avgVec(ageVec);
    }
    int births = 0;
    int deaths = 0;
    int living = 0;
    double avgNeighbors = 0;
    double avgAge = 0;
private:
    std::vector<int> neighborsVec;
    std::vector<int> ageVec;
};

class FinalAnalysis
{
public:
    std::vector<GenerationAnalysis> generations;
    void analyze(GenerationAnalysis generation)
    {
        finalAlive += generation.living;
        ageVec.push_back(generation.avgAge);
        neighborsVec.push_back(generation.avgNeighbors);
        birthsVec.push_back(generation.births);
        deathsVec.push_back(generation.deaths);
        aliveVec.push_back(generation.living);
        generationsCount++;
    }
    void finalize()
    {
        avgAge = MathTools::avgVec(ageVec);
        avgNeighbors = MathTools::avgVec(neighborsVec);
        avgBirths = MathTools::avgVec(birthsVec);
        avgDeaths = MathTools::avgVec(deathsVec);
        births = MathTools::sumVec(birthsVec);
        deaths = MathTools::sumVec(deathsVec);
    }
    void save(std::string fileName)
    {
        std::string out;
        out += "generations: " + std::to_string(generationsCount) + "\r\n";
        out += "avg_age: " + std::to_string(avgAge) + "\r\n";
        out += "avg_neighbors: " + std::to_string(avgNeighbors) + "\r\n";
        out += "avg_births: " + std::to_string(avgBirths) + "\r\n";
        out += "avg_deaths: " + std::to_string(avgDeaths) + "\r\n";
        out += "final_alive: " + std::to_string(finalAlive) + "\r\n";
        out += "births: " + std::to_string(births) + "\r\n";
        out += "deaths: " + std::to_string(deaths) + "\r\n";

        out += "------- \r\n";

        out += "age_vector: \r\n";;
        out += StringTools::vecToString(ageVec) + "\r\n";

        out += "neighbors_vector: \r\n";
        out += StringTools::vecToString(neighborsVec) + "\r\n";

        out += "births_vector:\r\n";
        out += StringTools::vecToString(birthsVec) + "\r\n";

        out += "deaths_vector:\r\n";
        out += StringTools::vecToString(deathsVec) + "\r\n";

        out += "alive_vector:\r\n";
        out += StringTools::vecToString(aliveVec) + "\r\n";

        FileIO::write(fileName, out);
    }
private:
    double avgAge = 0;
    double avgNeighbors = 0;
    double avgBirths = 0;
    double avgDeaths = 0;
    int births = 0;
    int deaths = 0;
    int finalAlive = 0;
    int generationsCount = 0;
    std::vector<double> ageVec;
    std::vector<double> neighborsVec;
    std::vector<double> birthsVec;
    std::vector<double> deathsVec;
    std::vector<int> aliveVec;
};