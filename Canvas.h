/*
A simple canvas class used for draw frames of the final image
*/
#include <vector>
#include "Matrix.h"

class Canvas : public Matrix
{
public:
    Canvas(int width, int height, int pxScale = 4) : Matrix(width*pxScale, height*pxScale, 4)
    {
        w = width;
        h = height;
        ps = pxScale;
    }
    void draw(int x, int y, std::vector<uint8_t> rgb = {255,255,255})
    {
        for(int yOff = 0; yOff < ps; yOff++)
        {
            for(int xOff = 0; xOff < ps; xOff++)
            {
                write(x+xOff, y+yOff, rgb);
            }
        }
    }
    void draw(int n, std::vector<uint8_t> rgb = {255,255,255})
    {
        std::vector<int> xy = getXY(n*ps);
        int x = xy[0];//*ps;
        int y = xy[1];//*ps;
        for(int yOff = 0; yOff < ps; yOff++)
        {
            for(int xOff = 0; xOff < ps; xOff++)
            {
                write(x+xOff, y+yOff, rgb);
            }
        }
        //write(n, rgb);
    }
private:
    int w;
    int h;
    int ps;
};