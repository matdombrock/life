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
        else if (pallet == "green")
        {
            uint8_t color = colorUp(val);
            uint8_t color2 = colorDown(val);
            pixel = {color2, 255, color};
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