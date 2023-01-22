/*
A simple canvas class used for draw frames of the final image
*/
#include <vector>
#include "Matrix.h"

class Canvas : public Matrix
{
public:
    Canvas(int width, int height) : Matrix(width, height, 4)
    {
        
    }
    void draw(int x, int y, std::vector<uint8_t> rgb = {255,255,255})
    {
        write(x, y, rgb);
    }
    void draw(int n, std::vector<uint8_t> rgb = {255,255,255})
    {
        write(n, rgb);
    }
private:
    
};