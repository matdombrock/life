/*
This is the main entry point

This is responsible for iterating through generations
The actual GOL logic is in `Petri.h`

It also holds logic for generating gifs
*/

#include <vector>
#include <cstdint>
#include <iostream>
#include <math.h>
#include <ctime>
#include "lib/gif.h"
#include "Matrix.h"
#include "Canvas.h"
#include "Petri.h"
#include "Organism.h"

#include "util/CLIO.h"

class Cfg
{
public:
    const char * fileName = "out/life";
    int delay = 32;
    int frames = 128;
    int width = 64;
    int height = 64;
    int scale = 8;
};

void init(Petri &dish, int t)
{
    //dish.randomize(t, 0.5f);
    dish.loadOrganism(Organisms::rune1);
}

void drawFrame1(Canvas &canvas, Cfg cfg)
{
    // Empty first frame
    canvas.clear();
    canvas.draw(0,0);
    canvas.draw(cfg.width-1, 0);
    canvas.draw(0,cfg.height-1);
    canvas.draw(cfg.width-1,cfg.height-1);
}

int main()
{
    Cfg cfg;

    GifWriter g;

    // Get the current timestamp
    std::time_t t = std::time(0);  // t is an integer type

    std::string fileName = cfg.fileName + std::to_string(t) + ".gif";// need to add timestamp

    int outputW = cfg.width * cfg.scale;
    int outputH = cfg.height * cfg.scale;
    GifBegin(&g, fileName.c_str(), outputW, outputH, cfg.delay);

    Canvas canvas(cfg.width, cfg.height, cfg.scale);
    
    // Empty first frame
    drawFrame1(canvas, cfg);
    auto frame = canvas.getBuffer();
    GifWriteFrame(&g, frame.data(), outputW, outputH, cfg.delay);
    
    Petri dish(cfg.width, cfg.height);

    init(dish, t);
    
	for(int i = 0; i < cfg.frames; i++)
	{
		
        CLIO::print("frame: "+std::to_string(i+1));

        canvas.clear();

        auto dishBuffer = dish.getBuffer();

        // Draw the Petri dish to the buffer
        for (int ii = 0; ii < dishBuffer.size(); ii++)
        {
            if (dishBuffer[ii] > 0)
            {
                uint8_t color = (dishBuffer[ii] * 16) < 255 ? (dishBuffer[ii] * 16) : 255;
                uint8_t color2 = 255 - (dishBuffer[ii] * 64) > 0 ? 255 - (dishBuffer[ii] * 64) : 0;
                std::vector<uint8_t> data = {color, 255, color2};
                canvas.draw(ii, data);
            }
        }
        int living = dish.nextGen();

        auto frame = canvas.getBuffer();

        // Delay the first generation
        int delay = i == 0 ? cfg.delay * 4 : cfg.delay;
		GifWriteFrame(&g, frame.data(), outputW, outputH, delay);
        if (living < 1){
            // all are dead
            CLIO::print("!!!Population Death!!!");
            break;
        }
	}

	GifEnd(&g);

	return 0;
}
