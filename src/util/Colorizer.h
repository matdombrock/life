#pragma once
#include <vector>
#include <cstdint>
#include <string>
class Colorizer
{
public:
    static std::vector<uint8_t> colorPixel(uint8_t val, std::string pallet = "white")
    {
        std::vector<uint8_t> pixel = {255,255,255};
        if (pallet == "white")
        {
            // Do nothing, white is the default
        }
        else if (pallet == "grey")
        {
            uint8_t color = 100 + (colorUp(val)/2);
            pixel = {color, color, color};
        }
        else if (pallet == "yellow")
        {
            uint8_t color = colorUp(val);
            uint8_t color2 = colorDown(val);
            pixel = {color2, 255, color};
        }
        else if (pallet == "ruby")
        {
            uint8_t color = colorUp(val);
            uint8_t color2 = colorDown(val);
            pixel = {color2, color, color};
        }
        else if (pallet == "barney")
        {
            uint8_t color = colorUp(val);
            uint8_t color2 = colorDown(val);
            pixel = {color2, color, color2};
        }
        else if (pallet == "slime")
        {
            uint8_t color = colorUp(val);
            uint8_t color2 = colorDown(val);
            pixel = {color, color2, color};
        }
        else if (pallet == "earth")
        {
            uint8_t color = colorUp(val);
            uint8_t color2 = colorDown(val);
            pixel = {color, 64, color2};
        }
        else if (pallet == "lime")
        {
            uint8_t color = colorUp(val);
            uint8_t color2 = colorDown(val);
            pixel = {color, 255, color};
        }
        else if (pallet == "rainbow")
        {
            if(val > 6)
            {
                pixel = {255, 0, 0};
            }
            else if(val > 5)
            {
                pixel = {255, 255, 0};
            }
            else if(val > 4)
            {
                pixel = {0, 255, 0};
            }
            else if(val > 3)
            {
                pixel = {0, 255, 255};
            }
            else if(val > 2)
            {
                pixel = {0, 0, 255};
            }
            else if(val > 1)
            {
                pixel = {255, 0, 255};
            }
            else 
            {
                pixel = {255, 255, 255};
            }
        }
        else if (pallet == "rainbow2")
        {
            if(val > 6)
            {
                pixel = {255, 0, 255};
            }
            else if(val > 5)
            {
                pixel = {255, 0, 0};
            }
            else if(val > 4)
            {
                pixel = {255, 255, 0};
            }
            else if(val > 3)
            {
                pixel = {0, 255, 0};
            }
            else if(val > 2)
            {
                pixel = {0, 255, 255};
            }
            else if(val > 1)
            {
                pixel = {0, 0, 255};
            }
            else 
            {
                pixel = {255, 255, 255};
            }
        }
        else if (pallet == "rainbow3")
        {
            if(val > 6)
            {
                pixel = {255, 255, 255};
            }
            else if(val > 5)
            {
                pixel = {255, 255, 0};
            }
            else if(val > 4)
            {
                pixel = {255, 0, 0};
            }
            else if(val > 3)
            {
                pixel = {255, 0, 255};
            }
            else if(val > 2)
            {
                pixel = {0, 0, 255};
            }
            else if(val > 1)
            {
                pixel = {0, 255, 255};
            }
            else 
            {
                pixel = {0, 255, 0};
            }
        }
        else if (pallet == "red")
        {
            uint8_t color = colorUp(val);
            pixel = {255, color, color};
        }
        else if (pallet == "green")
        {
            uint8_t color = colorUp(val);
            pixel = {color, 255, color};
        }
        else if (pallet == "blue")
        {
            uint8_t color = colorUp(val);
            uint8_t color2 = colorDown(val);
            pixel = {color, 255, color2};
        }
        return pixel;
    }
private:
    static uint8_t colorUp(uint8_t val)
    {
        return (val * 16) < 255 ? (val * 16) : 25;
    }
    static uint8_t colorDown(uint8_t val)
    {
        return 255 - (val * 16) > 0 ? 255 - (val * 16) : 0;
    }
};