/*
A simple canvas class used for draw frames of the final image
Inherits the matrix class
*/
#include <vector>
#include "Matrix.h"
#include "RGB.h"

class Canvas : public Matrix
{
public:
    Canvas(int width, int height, int scale) : Matrix(width * scale, height * scale, 4)
    {
        w = width;
        h = height;
        ds = 4;
        ps = scale;
    }
    void draw(int x, int y, RGB rgb = RGB())
    {
        x*=ps;// adjust for scale
        y*=ps;// adjust for scale
        for (int yOff = 0; yOff < ps; yOff++)
        {
            for (int xOff = 0; xOff < ps; xOff++)
            {
                writeXY(x+xOff, y+yOff, rgb);
            }
        }
    }
    void draw(int n, RGB rgb = RGB())
    {
        int x = n % w;
        int y = n / h;
        x*=ps;// adjust for scale
        y*=ps;// adjust for scale
        for (int yOff = 0; yOff < ps; yOff++)
        {
            for (int xOff = 0; xOff < ps; xOff++)
            {
                writeXY(x+xOff, y+yOff, rgb);
            }
        }
        //write(n, rgb);
    }
private:
  int w;
  int h;
  int ds;
  int ps;  
};