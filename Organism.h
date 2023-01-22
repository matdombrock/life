/*
A class and namespace for holding starter organisms
*/

#pragma once
#include <vector>
#include <cstdint>
#include "Pitri.h"

class Organism
{
public:
    Organism(std::vector<uint8_t> newData, int newWidth, int newHeight)
    {
        data = newData;
        width = newWidth;
        height = newHeight;
    }
    int width;
    int height;
    std::vector<uint8_t> data;
};

namespace Organisms
{
    Organism square2({
        1,1,
        1,1
    },2,2);
    Organism square3({
        1,1,1,
        1,1,1,
        1,1,1
    },3,3);
    Organism square3Osc({
        1,1,1,0,0,0,
        1,1,1,0,0,0,
        1,1,1,0,0,0,
        0,0,0,1,1,1,
        0,0,0,1,1,1,
        0,0,0,1,1,1,
    },6,6);
    Organism rune1({
        0,1,0,
        1,1,1,
        1,0,1,
        1,1,1,
        0,1,0
    },3,5);
    Organism rune1A({
        1,1,1,0,0,0,1,1,1,
        1,0,1,0,0,0,1,0,1,
        1,1,1,0,0,0,1,1,1,
    },9,3);
    Organism rune1A2({
        1,1,1,0,0,0,1,1,1,
        1,0,1,0,0,0,1,0,1,
        1,1,1,0,0,0,1,1,1,
        0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,
        1,1,1,0,0,0,1,1,1,
        1,0,1,0,0,0,1,0,1,
        1,1,1,0,0,0,1,1,1,
    },9,9);
}