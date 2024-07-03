#pragma once
#include <string>
#include <vector>
#include "Petri.h"
#include "Organism.h"
#include "util/FileIO.h"
#include "util/CLIO.h"
#include "util/StringTools.h"

class SorgLoader
{
public:
    static void load(Petri &dish, std::string fileName, int xOff=0, int yOff=0, bool center=true)
    {
        CLIO::print("Loading .sorg file: "+fileName);
        auto lines = FileIO::readLines(fileName);
        if (lines.empty())
        {
            CLIO::print("Cant load .sorg file: "+fileName);
            return;
        }
        lines = stripComments(lines);
        lines = stripSpaces(lines);
        int w = countCols(lines);
        int h = countRows(lines);
        
        std::vector<uint8_t> buffer = createBuffer(lines);

        Organism org(buffer, w, h);

        dish.loadOrganism(org, xOff, yOff, center);

        CLIO::print("---");
        CLIO::print("Loaded .sorg file: "+fileName);
        CLIO::print(w);
        CLIO::print(h);
        CLIO::print("---");
    }
private:
    static std::vector<std::string> stripComments(std::vector<std::string> lines)
    {
        std::vector<std::string> goodLines;
        for (int i = 0; i < lines.size(); i++)
        {
            std::string line = lines[i];
            if (line[0] == '#')
            {
                // Comments are ignored
                continue;
            }
            // We found a data line
            goodLines.push_back(line);
        }
        return goodLines;
    }
    static std::vector<std::string> stripSpaces(std::vector<std::string> lines)
    {
        // Assumes comments have been stripped
        std::vector<std::string> goodLines;
        for (int i = 0; i < lines.size(); i++)
        {
            std::string line = lines[i];
            line = StringTools::removeSpaces(line);
            goodLines.push_back(line);
        }
        return goodLines;
    }
    static int countCols(std::vector<std::string> lines)
    {
        // Assumes comments have been stripped
        return lines[0].size();
    }
    static int countRows(std::vector<std::string> lines)
    {
        // Assumes comments have been stripped
        return lines.size();
    }
    static std::vector<uint8_t> createBuffer(std::vector<std::string> lines)
    {
        std::vector<char> offChars = {'0','O','o'}; 
        std::vector<uint8_t> buffer;
        for (int i = 0; i < lines.size(); i++)
        {
            std::string line = lines[i];
            for(int ch = 0; ch < line.size(); ch++)
            {
                if(std::count(offChars.begin(), offChars.end(), line[ch]))
                {
                    // char is off
                    buffer.push_back(0);
                }
                else
                {
                    // Not off is assumed on
                    buffer.push_back(1);
                }
            }
        }
        return buffer;
    }
};