#pragma once
#include <vector>
#include <algorithm>
#include "util/CLIO.h"
#include "util/FileIO.h"
#include "Cfg.h"
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
            // clear spaces
            std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
            line.erase(end_pos, line.end());

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
            else if (key == "rules")
            {
                strcpy(cfg.ruleSet, val.c_str());
            }
        }
        CLIO::print("Loaded config file!");
        return cfg;
    }
};