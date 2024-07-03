/*
A simple 2d matrix class
Stores data as a 1d vector

This is the basic building block for the simulation as well as the graphics output
*/

#pragma once
#include <iostream>
#include <vector>
#include <cstdint>
#include "RGB.h"
#include "util/CLIO.h"

class Matrix
{
public:
    Matrix(int width, int height, int dataSize = 1)
    {
        w = width;
        h = height;
        ds = dataSize;
        //std::vector<uint8_t> ds1 = {1};
        //std::vector<uint8_t> ds4 = {255,255,255};
        buffer.resize(w * h * dataSize);
        std::fill(buffer.begin(), buffer.end(), 0);
    }
    void clear()
    {
        std::fill(buffer.begin(), buffer.end(), 0);
    }
    void clone(Matrix copySource)
    {
        buffer = copySource.getBuffer();
    }
    std::vector<uint8_t> getBuffer()
    {
        return buffer;
    }
    int getWidth() {return w;};
    int getHeight() {return h;};
    void writeXY(int x, int y, RGB rgb = RGB())
    {
        int index = getIndex(x,y);
        writeAtIndex(index, rgb);
    }
    void writeN(int n, RGB rgb = RGB())
    {
        n *= ds;
        writeAtIndex(n, rgb);
    }
    uint8_t read(int x, int y)
    {
        int index = getIndex(x,y);
        return buffer[index];
    }
    uint8_t read(int n)
    {
        return buffer[n];
    }
    int getSize()
    {
        return buffer.size();
    }
private:
    int getIndex(int x, int y)
    {
        x*=ds;
        y*=ds;
        return (w*y)+x;
    }
    void writeAtIndex(int n, RGB rgb = RGB())
    {
        if(ds == 1)
        {
            // This is a single item data point
            buffer[n] = rgb.r;
        }
        else if(ds == 4)
        {
            // RGBA
            buffer[n] = rgb.r;
            buffer[n+1] = rgb.g;
            buffer[n+2] = rgb.g;
            buffer[n+3] = 255;// Alpha not supported
        }
        else
        {
            CLIO::print("Error: Bad data size!");
        }
    }
    int w;
    int h;
    int ds;
    std::vector<uint8_t> defaultData;
    std::vector<uint8_t> buffer;
};