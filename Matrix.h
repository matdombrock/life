/*
A simple 2d matrix class
Stores data as a 1d vector

This is the basic building block for the simulation as well as the graphics output
*/

#pragma once
#include <iostream>
#include <vector>
#include <cstdint>

class Matrix
{
public:
    Matrix(int width, int height, int dataSize = 1)
    {
        w = width * dataSize;
        h = height * dataSize;
        ds = dataSize;
        defaultData = dataSize == 1 ? (std::vector<uint8_t>){1} : (std::vector<uint8_t>){255,255,255};
        buffer.resize(w * h);
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
    void write(int x, int y, std::vector<uint8_t> data = {})
    {
        if (data.empty()){data = defaultData;}
        x*=ds;
        y*=ds;
        int index = getIndex(x,y);
        writeAtIndex(index, data);
    }
    void write(int n, std::vector<uint8_t> data = {})
    {
        if (data.empty()){data = defaultData;}
        n *= ds;
        writeAtIndex(n, data);
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
    std::vector<int> getXY(int n)
    {
        n *= ds;
        int x = (n % h);
        int y = (n / w);
        std::vector<int> res = {x,y};
        return res;
    }
private:
    int getIndex(int x, int y)
    {
        // There are 4 items per pixel
        // RGBAx
        //x*=ds;
        //y*=ds;// Was breaking
        if(x >= w)
        {
            std::cout << "Offset Error" << std::endl;
            //x = w-1;
        }
        if(y >= h)
        {
            std::cout << "Offset Error" << std::endl;
            //y=h-1;
        }
        return (w*y)+x;
    }
    void writeAtIndex(int n, std::vector<uint8_t> data)
    {
        if(ds == 1)
        {
            // This is a single item data point
            buffer[n] = data[0];
        }
        else if(ds == 4)
        {
            // There are 4 items per pixel
            // RGBA
            // ensure that data is the right size
            if (data.size() >= 3)
            {
                buffer[n] = data[0];
                buffer[n+1] = data[1];
                buffer[n+2] = data[2];
                buffer[n+3] = 255;// Alpha is not supported
            }
        }
        else
        {
            std::cout << "Error: Bad data size!" << std::endl;
        }
    }
    int w;
    int h;
    int ds;
    std::vector<uint8_t> defaultData;
    std::vector<uint8_t> buffer;
};