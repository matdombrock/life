#pragma once
#include <vector>
#include <string>
#include "util/MathTools.h"
#include "util/StringTools.h"
#include "util/FileIO.h"
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
        ageVec.push_back(generation.avgAge);
        neighborsVec.push_back(generation.avgNeighbors);
        birthsVec.push_back(generation.births);
        deathsVec.push_back(generation.deaths);
        aliveVec.push_back(generation.living);
        generationsCount++;
        peakAgeVec.push_back(generation.peakAge);
        frozen = generation.frozen;
        popDeath = generation.popDeath;
    }
    void finalize()
    {
        avgAge = MathTools::avgVec(ageVec);
        avgNeighbors = MathTools::avgVec(neighborsVec);
        avgBirths = MathTools::avgVec(birthsVec);
        avgDeaths = MathTools::avgVec(deathsVec);
        births = MathTools::sumVec(birthsVec);
        deaths = MathTools::sumVec(deathsVec);
        finalAlive = aliveVec[MathTools::max((int)aliveVec.size() - 1, 0)];
        peakAge = MathTools::maxVec(peakAgeVec);
    }
    void save(std::string fileNameAna, std::string fileName)
    {
        std::string out;
        out += R"(
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.4/Chart.js">
</script>
</head>
<body>
<canvas id="myChart" style="max-width:90vw; margin: 0 auto"></canvas>
<hr>
<style>
    html{
        background:black;
        color:white;
        font-family:monospace;
        padding:2rem;
        text-align: center;
    }
    img{
        width:55vw; 
        max-width:90vw; 
    }
    p{
        padding:1rem;
        text-align: left;
    }
</style>
<script>
)";
        std::string birthsVecS = StringTools::vecToString(birthsVec);
        std::string deathsVecS = StringTools::vecToString(deathsVec);
        std::string aliveVecS = StringTools::vecToString(aliveVec);
        std::string ageVecS = StringTools::vecToString(ageVec);
        std::string peakAgeVecS = StringTools::vecToString(peakAgeVec);
        std::string neighborsVecS = StringTools::vecToString(neighborsVec);

        std::vector<int> xVals;
        for(int i = 0; i < generationsCount; i++)
        {
            xVals.push_back(i);
        }
        std::string xValsS = StringTools::vecToString(xVals);

        out += "const xValues = [" + xValsS + "];";
        out += "const births = [" + birthsVecS + "];";
        out += "const deaths = [" + deathsVecS + "];";
        out += "const alive = [" + aliveVecS + "];";
        out += "const age = [" + ageVecS + "];";
        out += "const peakAge = [" + peakAgeVecS + "];";
        out += "const neighbors = [" + neighborsVecS + "];";
        out += R"(
new Chart('myChart', {
  type: 'line',
  data: {
    labels: xValues,
    datasets: [
        {
            backgroundColor: 'rgba(255,255,255,1.0)',
            borderColor: 'rgba(100,255,100,1.0)',
            data: births,
            label: "Births",
            fill:false
        },
        {
            backgroundColor: 'rgba(255,255,255,1.0)',
            borderColor: 'rgba(255,100,100,1.0)',
            data: deaths,
            label: "Deaths",
            fill:false
        },
        {
            backgroundColor: 'rgba(255,255,255,1.0)',
            borderColor: 'rgba(100,100,255,1.0)',
            data: alive,
            label: "Alive",
            fill:false
        },
        {
            backgroundColor: 'rgba(255,255,255,1.0)',
            borderColor: 'rgba(255,100,155,1.0)',
            data: age,
            label: "Avg. Age",
            fill:false,
            hidden: true,
        },
        {
            backgroundColor: 'rgba(255,255,255,1.0)',
            borderColor: 'rgba(255,255,100,1.0)',
            data: peakAge,
            label: "Peak Age",
            fill:false,
            hidden: true,
        },
        {
            backgroundColor: 'rgba(255,255,255,1.0)',
            borderColor: 'rgba(100,255,255,1.0)',
            data: neighbors,
            label: "Neighbors",
            fill:false,
            hidden: true,
        },
    ]
  },
  options:{
    elements: {
        line: {
            tension: 0
        }
    }
  }
});
Chart.defaults.global.defaultFontColor = "#fff";
</script>
)";
       
        out += "<img src='"+fileName+".gif'><br>";

        out += "<hr>";

        out += "<p>";
        out += "--- </br>";
        out += "Final Analysis: </br>";
        out += "--- </br>";
        out += "</br>";
        out += "generations: " + std::to_string(generationsCount) + "</br>";
        out += "peak_age: " + std::to_string(peakAge) + "</br>";
        out += "avg_age: " + std::to_string(avgAge) + "</br>";
        out += "avg_neighbors: " + std::to_string(avgNeighbors) + "</br>";
        out += "avg_births: " + std::to_string(avgBirths) + "</br>";
        out += "avg_deaths: " + std::to_string(avgDeaths) + "</br>";
        out += "final_alive: " + std::to_string(finalAlive) + "</br>";
        out += "births: " + std::to_string(births) + "</br>";
        out += "deaths: " + std::to_string(deaths) + "</br>";
        out += "froze: " + std::to_string(frozen) + "</br>";
        out += "population_died: " + std::to_string(popDeath) + "</br>";
        out += "</p>";
        
        out += "</br>";
        out += "<hr>";

        out += "<p>";
        out += "--- </br>";
        out += "cfg.txt </br>";
        out += "--- </br>";
        out += "</br>";

        std::vector<std::string> cfgLines = FileIO::readLines("./cfg.txt");
        for (auto line : cfgLines)
        {
            out += line + "</br>";
        }

        out += "</p>";
        out += "</body>";
        
        
        FileIO::write(fileNameAna, out);
    }
private:
    double avgAge = 0;
    int peakAge = 0;
    double avgNeighbors = 0;
    double avgBirths = 0;
    double avgDeaths = 0;
    int births = 0;
    int deaths = 0;
    int finalAlive = 0;
    int generationsCount = 0;
    //
    bool frozen = false;
    bool popDeath = false;
    //
    std::vector<double> ageVec;
    std::vector<double> peakAgeVec;
    std::vector<double> neighborsVec;
    std::vector<double> birthsVec;
    std::vector<double> deathsVec;
    std::vector<int> aliveVec;
};