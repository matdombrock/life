/*
Contains the actual Game of Life logic
This uses 2 instances of the Matrix class
But does not inherit the class itself (like Canvas)
*/

#pragma once
#include <vector>
#include <map>
//#include <iterator>
#include "Matrix.h"
#include "Organism.h"
#include "Analysis.h"
#include "util/CLIO.h"

class Petri
{
public:
    Petri(int width, int height, char newRuleSet[4]) : matrix(width, height), matrix2(width, height)
    {
        w = width;
        h = height;
        ruleSet[0] = newRuleSet[0];
        ruleSet[1] = newRuleSet[1];
        ruleSet[2] = newRuleSet[2];
        ruleSet[3] = newRuleSet[3];
    }
    void randomize(unsigned seed, float f = 0.5f)
    {
        std::srand(seed);
        f = 1 - f; // invert
        for (int i = 0; i < matrix2.getSize(); i++)
        {
            uint8_t rand = (std::rand() > (RAND_MAX * f)) ? 1 : 0;

            if (rand)
            {
                alive(i);
            }
        }
    }
    std::vector<uint8_t> getBuffer()
    {
        return matrix.getBuffer();
    }
    void thrive(std::uint8_t &cellState, bool force = false)
    {
        // The cell is born
        if ( force == true)
        {
            cellState = 1;
            return;
        }
        cellState++;
    }
    void survive(std::uint8_t &cellState)
    {
        // The cell lives happily 
        // But only if it is alive
        // No cells are born
        cellState = cellState > 0 ? cellState + 1 : cellState;
    }
    void death(std::uint8_t &cellState)
    {
        cellState = 0;
    }
    void runRule(char rule, std::uint8_t &cellState)
    {
        if (rule == 'd'){death(cellState);}
        else if (rule == 's'){survive(cellState);}
        else if (rule == 't'){thrive(cellState);}
    }
    GenerationAnalysis nextGen()
    {
        GenerationAnalysis analysis;
        // clear the next gen buffer
        matrix2.clear();
        for (int i = 0; i < matrix.getSize(); i++)
        {
            // Define the indicies we need to check for this cell
            int up = i - w;
            int upLeft = up - 1;
            int upRight = up + 1;
            int down = i + w;
            int downLeft = down - 1;
            int downRight = down + 1;
            int right = i + 1;
            int left = i - 1;

            // Define some flags
            bool rowStart = i % w == 0;// Are we at the start of a row?
            bool rowEnd = ( i + 1) % w == 0;// Are we at the end of a row?
            bool rowFirst = up <= 0;// Are we on the first row?
            bool rowLast = down >= matrix.getSize()-1;// Are we on the last row?
            
            int neighbors = 0;

            //
            // Up
            if(!rowFirst && matrix.read(up) >= 1) {neighbors++;}
            // Up Left
            if(!rowFirst && !rowStart && matrix.read(upLeft) >= 1) {neighbors++;}
            // Up Right
            if(!rowFirst && !rowEnd && matrix.read(upRight) >= 1) {neighbors++;}
            // Down
            if(!rowLast && matrix.read(down) >= 1) {neighbors++;}
            // Down Left
            if(!rowLast && !rowStart && matrix.read(downLeft) >= 1) {neighbors++;}
            // Down Right
            if(!rowLast && !rowEnd && matrix.read(downRight) >= 1) {neighbors++;}
            // Right
            if(!rowEnd && matrix.read(right) >= 1) {neighbors++;}
            // Right
            if(!rowStart && matrix.read(left) >= 1) {neighbors++;}
            //

            // check if the cell is currently alive
            auto cellState = matrix.read(i);
            bool wasAlive = cellState > 0;

            if (neighbors < 2)
            {
                runRule(ruleSet[0], cellState);
            }
            if (neighbors == 2)
            {
                runRule(ruleSet[1], cellState);
            }
            if (neighbors == 3)
            {
                runRule(ruleSet[2], cellState);
            }
            if (neighbors > 3)
            {
                runRule(ruleSet[3], cellState);
            }

            // Check if the cell died
            if (wasAlive && cellState < 1)
            {
                // Died
                analysis.death();
            }
            // Check if the cell was born
            if (!wasAlive && cellState > 0)
            {
                // Born
                analysis.birth();
            }
            if (cellState > 0)
            {
                analysis.alive();
            }

            if (cellState > 0){
                analysis.setAge(cellState);
                analysis.setNeighbors(neighbors);
            }
            //
            std::vector<uint8_t> data = {cellState};
            matrix2.writeN(i, data);
        }
        analysis.finalize();
        // copy the buffer back to the original
        matrix.clone(matrix2);
        return analysis;
    }
    void alive(int x, int y, std::vector<uint8_t> data = {1})
    {
        int index = getIndex(x, y);
        aliveAtIndex(index, data);
    }
    void alive(int n, std::vector<uint8_t> data = {1})
    {
        aliveAtIndex(n, data);
    }
    void loadOrganism(Organism organism, int xOff = 0, int yOff = 0, bool center = true)
    {
        if (center)
        {
            xOff = (w / 2) - (organism.width / 2) + xOff;
            yOff = (h / 2) - (organism.height / 2) + yOff;
        }
        int i = 0;
        for (int y = 0; y < organism.height; y++)
        {
            for (int x = 0; x < organism.width; x++)
            {
                auto data = organism.data[i];
                alive(x + xOff, y + yOff, {data});
                i++;
            }
        }
    }
    int getWidth() { return w; };
    int getHeight() { return h; };
private:
    int w;
    int h;
    Matrix matrix;
    Matrix matrix2;
    char ruleSet[4];
    int getIndex(int x, int y, std::vector<uint8_t> data = {1})
    {
        return (w * y) + x;
    }
    void aliveAtIndex(int n, std::vector<uint8_t> data = {1})
    {
        matrix.writeN(n, data);
    }
};