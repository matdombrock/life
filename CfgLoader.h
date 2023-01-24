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
    std::string pallet = "white";
    std::string sorg = "noise";
    bool sorgCenter = true;
    int sorgXOff = 0;
    int sorgYOff = 0;
    bool copyCfg = false;
    char ruleSet[4] = {'d','s','t','d'};// game of life = {'d','s','t','d'}
};

class CfgLoader
{
public:
    static Cfg load()
    {
        Cfg cfg;
        std::vector<std::string> cfgText = FileIO::readLines("./cfg.txt");
        if(cfgText.empty())
        {
            CLIO::print("Can't find config file!");
            return cfg;
        }
        for(std::string line : cfgText)
        {
            line = StringTools::removeSpaces(line);

            if(line[0] == '#' || line[0] == '-' || line.empty())
            {
                // ignore comments and empty lines
                continue;
            }

            int delimiterIndex = line.find("=");
            std::string key = line.substr(0, delimiterIndex);
            std::string val = line.substr(delimiterIndex + 1, line.size() - 1);
            if (key == "file")
            {
                //cfg.fileName = val.c_str();
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
            else if (key == "pallet")
            {
                cfg.pallet = val;
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
            else if (key == "copy_cfg")
            {
                cfg.copyCfg = (bool)std::stoi(val);
            }
            else if (key == "rules")
            {
                strcpy(cfg.ruleSet, val.c_str());
            }
            else
            {
                CLIO::print("Unknown config line:");
                CLIO::print(line);
            }
        }
        CLIO::print("Loaded config file!");
        return cfg;
    }
};