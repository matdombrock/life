#pragma once
#include <vector>
#include <string>
#include "util/MathTools.h"
#include "util/StringTools.h"
#include "util/FileIO.h"
#include "AnalysisData.h"
#include "HTML.h"
class GenerationAnalysis
{
public:
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
        peakAge = MathTools::max(count, peakAge);
    }
    void finalize()
    {
        avgNeighbors = MathTools::avgVec(neighborsVec);
        avgAge = MathTools::avgVec(ageVec);
        frozen = births == 0 && deaths == 0;
        popDeath = living == 0;
    }
    int births = 0;
    int deaths = 0;
    int living = 0;
    double avgNeighbors = 0;
    double avgAge = 0;
    int peakAge = 0;
    bool frozen = false;
    bool popDeath = false;

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
        data.ageVec.push_back(generation.avgAge);
        data.neighborsVec.push_back(generation.avgNeighbors);
        data.birthsVec.push_back(generation.births);
        data.deathsVec.push_back(generation.deaths);
        data.aliveVec.push_back(generation.living);
        data.generationsCount++;
        data.peakAgeVec.push_back(generation.peakAge);
        data.frozen = generation.frozen;
        data.popDeath = generation.popDeath;
    }
    void finalize()
    {
        data.avgAge = MathTools::avgVec(data.ageVec);
        data.avgNeighbors = MathTools::avgVec(data.neighborsVec);
        data.avgBirths = MathTools::avgVec(data.birthsVec);
        data.avgDeaths = MathTools::avgVec(data.deathsVec);
        data.births = MathTools::sumVec(data.birthsVec);
        data.deaths = MathTools::sumVec(data.deathsVec);
        data.finalAlive = data.aliveVec[MathTools::max((int)data.aliveVec.size() - 1, 0)];
        data.peakAge = MathTools::maxVec(data.peakAgeVec);
    }
    void save(std::string fileNameAna, std::string fileName, std::string cfgString)
    {
        CLIO::print("Building HTML...");
        std::string out = HTML::buildHTML(data, fileName, cfgString);   
        CLIO::print("Writing HTML...");
        FileIO::write(fileNameAna, out);
    }

private:
    AnalysisData data;
};