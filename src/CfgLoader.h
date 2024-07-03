#pragma once
#include <vector>
#include <algorithm>
#include "Petri.h"
#include "util/CLIO.h"
#include "util/FileIO.h"
#include "util/StringTools.h"

class Cfg
{
public:
    //const char * fileName = "life";
    std::string fileName = "life";
    int delay = 16;
    int frames = 64;
    int pre = 0; // Frames before render
    int width = 64;
    int height = 64;
    int scale = 4;
    std::string palette = "white";
    std::string sorg = "noise";
    bool sorgCenter = true;
    int sorgXOff = 0;
    int sorgYOff = 0;
    char ruleSet[4] = {'d','s','t','d'};// game of life = {'d','s','t','d'}
    std::string toString(bool comments = true)
    {
        std::string str = "";
        if (comments) str += "# Output file name \n";
        str += "file = " + fileName + "\n \n";
        if (comments) str += "# Gif frame delay (ms) \n";
        str += "delay = " + std::to_string(delay) + "\n \n";
        if (comments) str += "# Frames to render \n";
        str += "frames = " + std::to_string(frames) + "\n \n";
        if (comments) str += "# Generations to run before render \n";
        str += "pre = " + std::to_string(pre) + "\n \n";
        if (comments) str += "# Image / Simulation width \n";
        str += "width = " + std::to_string(width) + "\n \n";
        if (comments) str += "# Image / Simulation height \n";
        str += "height = " + std::to_string(height) + "\n \n";
        if (comments) str += "# Scale image up N times \n";
        str += "scale = " + std::to_string(scale) + "\n \n";
        if (comments) str += "# Color palette \n";
        if (comments) str += "# white | grey | yellow | ruby | barney | slime | earth | lime | rainbow | rainbow2 | rainbow3 | red | green | blue \n";
        str += "palette = " + palette + "\n \n";
        if (comments) str += "# Rules set (dstd) \n";
        str += "rules = " + std::string(ruleSet, 4) + " \n \n";
        if (comments) str += "---\n# Organism settings:\n---\n";
        if (comments) str += "# Organism file to load (*.sorg) \n";
        str += "sorg = " + sorg + "\n \n";
        if (comments) str += "# Center (0|1) \n";
        str += "sorg_center = " + std::to_string(sorgCenter) + "\n \n";
        if (comments) str += "# X offset (can be negative) \n";
        str += "sorg_x = " + std::to_string(sorgXOff) + "\n \n";
        if (comments) str += "# Y offset (can be negative) \n";
        str += "sorg_y = " + std::to_string(sorgYOff) + "\n \n";
        return str;
    }
};

class CfgLoader
{
public:
    static Cfg load(std::string cfgPath)
    {
        Cfg cfg;
        std::vector<std::string> cfgText = FileIO::readLines(cfgPath);
        if(cfgText.empty())
        {
            CLIO::print("Error: Can't find config file: " + cfgPath);
            CLIO::print("\nWrote an example config file: " + cfgPath);
            CLIO::print("Edit this file and try again.");
            FileIO::write(cfgPath, cfg.toString());
            // We could just return the default config here but better to exit
            exit(1);
        }
        int lineNum = 0; // Just a counter for debug
        for(std::string line : cfgText)
        {
            lineNum++;
            line = StringTools::removeSpaces(line);

            if(line[0] == '#' || line[0] == ' ' || line[0] == '-' || line == "\n" || line == "\n" || line.size() < 4 || line.empty() )
            {
                // ignore comments and empty lines
                continue;
            }

            int delimiterIndex = line.find("=");
            std::string key = line.substr(0, delimiterIndex);
            std::string val = line.substr(delimiterIndex + 1, line.size() - 1);
            if (key == "file")
            {
                cfg.fileName = val.c_str();
            }
            else if (key == "delay")
            {
                cfg.delay = std::stoi(val);
            }
            else if (key == "frames")
            {
                cfg.frames = std::stoi(val);
            }
            else if (key == "pre")
            {
                cfg.pre = std::stoi(val);
            }
            else if (key == "width")
            {
                cfg.width = std::stoi(val);
            }
            else if (key == "height")
            {
                cfg.height = std::stoi(val);
            }
            else if (key == "scale")
            {
                cfg.scale = std::stoi(val);
            }
            else if (key == "palette")
            {
                cfg.palette = val;
            }
            else if (key == "sorg")
            {
                cfg.sorg = val;
            }
            else if (key == "sorg_center")
            {
                cfg.sorgCenter = (bool)std::stoi(val);
            }
            else if (key == "sorg_x")
            {
                cfg.sorgXOff = std::stoi(val);
            }
            else if (key == "sorg_y")
            {
                cfg.sorgYOff = std::stoi(val);
            }
            else if (key == "rules")
            {
                strcpy(cfg.ruleSet, val.c_str());
            }
            else
            {
                CLIO::print("Unknown config line(" + std::to_string(lineNum) + "):");
                CLIO::print(line);
                exit(1);
            }
        }
        CLIO::print("Loaded config file!");
        return cfg;
    }
};