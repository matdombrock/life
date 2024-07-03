#pragma once
#include <string>
#include <vector>
#include "util/StringTools.h"
#include "util/FileIO.h"
#include "AnalysisData.h"
typedef std::vector<double> dvec;


class HTML
{
public:
    static std::string buildHTML(AnalysisData data, std::string fileName, std::string cfgString)
    {
        std::string birthsVecS = StringTools::vecToString(data.birthsVec);
        std::string deathsVecS = StringTools::vecToString(data.deathsVec);
        std::string aliveVecS = StringTools::vecToString(data.aliveVec);
        std::string ageVecS = StringTools::vecToString(data.ageVec);
        std::string peakAgeVecS = StringTools::vecToString(data.peakAgeVec);
        std::string neighborsVecS = StringTools::vecToString(data.neighborsVec);

        std::vector<int> xVals;
        for (int i = 0; i < data.generationsCount; i++)
        {
            xVals.push_back(i);
        }
        std::string xValsS = StringTools::vecToString(xVals);

        std::string out = "";
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

        out += "<img src='" + fileName + ".gif'><br>";

        out += "<hr>";

        out += "<p>";
        out += "--- </br>";
        out += "Final Analysis: </br>";
        out += "--- </br>";
        out += "</br>";
        out += "generations: " + std::to_string(data.generationsCount) + "</br>";
        out += "peak_age: " + std::to_string(data.peakAge) + "</br>";
        out += "avg_age: " + std::to_string(data.avgAge) + "</br>";
        out += "avg_neighbors: " + std::to_string(data.avgNeighbors) + "</br>";
        out += "avg_births: " + std::to_string(data.avgBirths) + "</br>";
        out += "avg_deaths: " + std::to_string(data.avgDeaths) + "</br>";
        out += "final_alive: " + std::to_string(data.finalAlive) + "</br>";
        out += "births: " + std::to_string(data.births) + "</br>";
        out += "deaths: " + std::to_string(data.deaths) + "</br>";
        out += "froze: " + std::to_string(data.frozen) + "</br>";
        out += "population_died: " + std::to_string(data.popDeath) + "</br>";
        out += "</p>";

        out += "</br>";
        out += "<hr>";

        out += "<p>";
        out += "--- </br>";
        out += "cfg.txt </br>";
        out += "--- </br>";
        out += "</br>";

        out += "<pre style='text-align:left'>" + cfgString + "</pre>";

        out += "</p>";
        out += "</body>";
        
        return out;
    }
};