/*
Contains the actual Game of Life logic
*/

#pragma once
#include <vector>
#include "Matrix.h"
#include "Organism.h"

class Pitri
{
public:
    Pitri(int width, int height) : matrix(width, height), matrix2(width, height)
    {
        w = width;
        h = height;
    }
    void randomize(unsigned seed, float f = 0.5f)
    {
        std::srand(seed);
        f = 1 - f;// invert
        for (int i = 0; i < matrix2.getSize(); i++)
        {
            uint8_t rand = (std::rand() > (RAND_MAX * f)) ? 1 : 0;

            if(rand)
            {
                alive(i);
            }
        }
    }
    std::vector<uint8_t> getBuffer()
    {
        return matrix.getBuffer();
    }
    int nextGen()
    {
        //
        // This logis is messy and needs to be cleaned up
        //

        // clear the next gen buffer
        matrix2.clear();
        int living = 0;
        for (int i = 0; i < matrix.getSize(); i++)
        {
            int neighbors = 0;
            // ensure we can go up
            int up = i - w;
            if (up >= 0)
            {
                // we are safe to go up a row
                // Check UP
                if (matrix.read(up) == 1)
                {
                    // We have a neighbor one row up
                    neighbors++;
                }
                // check up left
                // ensure we are not at the start of the row
                if (i - 1 > i / w)
                {
                    if (matrix.read(up - 1) == 1)
                    {
                        neighbors++;
                    }
                }
                // check up right
                // ensure we are not at the end of the row
                if ((i%w) + 1 < w || true)
                {
                    if (matrix.read(up + 1) == 1)
                    {
                        neighbors++;
                    }
                }
            }
            // ensure we can go right
            int right = i + 1;
            if ((i % w) + 1 < w || true)
            {
                if (matrix.read(right) == 1)
                {
                    neighbors++;
                }
            }
            // ensure we can go down
            int down = i + w;
            if(down < matrix.getSize())
            {
                // we can go down
                // check down
                if (matrix.read(down) == 1)
                {
                    neighbors++;
                }
            }
            // check down left
            // ensure we are not at the start of the row
            if (i - 1 > i / w)
            {
                if (matrix.read(down - 1) == 1)
                {
                    neighbors++;
                }
            }
            // check down right
            // ensure we are not at the end of the row
            if ((i%w) + 1 < w || true)
            {
                if (matrix.read(down + 1) == 1)
                {
                    neighbors++;
                }
            }
            // ensure we can check left
            int left = i - 1;
            if (left > i / w)
            {
                if (matrix.read(left) == 1)
                {
                    neighbors++;
                }
            }

            // check if the cell is currently alive
            auto isAlive = matrix.read(i);

            if (neighbors < 2)
            {
                //alive = 0;
                if(isAlive > 0)
                {
                    //std::cout << "die" << std::endl;
                    //std::cout << neighbors << std::endl;
                }
                    
                isAlive = 0;
            }
            if (neighbors == 2 || neighbors == 3)
            {
                //alive = alive;
            }
            if (neighbors > 3)
            {
                isAlive = 0;
                //std::cout << "overpop" << std::endl;
            }
            if (neighbors == 3)
            {
                // born if empty
                isAlive = 1;
                //std::cout << "born" << std::endl;
            }
            if (isAlive)
            {
                living++;
                //matrix2.write(i, alive);
                matrix2.write(i);
            }
            
        }
        // copy the buffer back to the original
        matrix.clone( matrix2 );
        return living;
    }
    int getWidth() {return w;};
    int getHeight() {return h;};
    void alive(int x, int y, std::vector<uint8_t> data = {1})
    {
        int index = getIndex(x,y);
        aliveAtIndex(index, data);
    }
    void alive(int n, std::vector<uint8_t> data = {1})
    {
        //n *= 4; ???
        aliveAtIndex(n, data);
    }
    void loadOrganism(Organism organism, int xOff=0, int yOff=0, bool center = true)
    {
        if (center)
        {
            xOff = ( w / 2 ) - ( organism.width / 2) + xOff;
            yOff = ( h / 2 ) - ( organism.height / 2) + yOff;
        }
        int i = 0;
        for (int y = 0; y < organism.height; y++)
        {
            for (int x = 0; x < organism.width; x++)
            {
                auto data = organism.data[i];
                alive(x+xOff,y+yOff, {data});
                i++;
            }
        }
    }
private:
    int w;
    int h;
    Matrix matrix;
    Matrix matrix2;
    int getIndex(int x, int y, std::vector<uint8_t> data = {1})
    {
        return (w*y)+x;
    }
    void aliveAtIndex(int n, std::vector<uint8_t> data = {1})
    {
        matrix.write(n, data);
    }
};