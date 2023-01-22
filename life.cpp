/*
This is the main entry point

This is responsible for iterating through generations
The actual GOL logic is in `Pitri.h`

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
#include "Pitri.h"
#include "Organism.h"

class Cfg
{
public:
    const char * fileName = "out/life";
    int delay = 8;
    int frames = 1024*2;
    int width = 256;//256
    int height = 256;//256
};

void init(Pitri &dish, int t)
{
    //Organism organism = Organisms::rune1;
    //dish.loadOrganism(Organisms::square3);
    //dish.loadOrganism(Organisms::square3,4,0);
    //dish.loadOrganism(Organisms::square3,-4,0);

    dish.randomize(t, 0.25f);
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

    std::time_t t = std::time(0);  // t is an integer type
    std::string fileName = cfg.fileName + std::to_string(t) + ".gif";// need to add timestamp
    GifBegin(&g, fileName.c_str(), cfg.width, cfg.height, cfg.delay);

    Canvas canvas(cfg.width, cfg.height);
    // Empty first frame
    drawFrame1(canvas, cfg);
    auto frame = canvas.getBuffer();
    GifWriteFrame(&g, frame.data(), cfg.width, cfg.height, cfg.delay);
    
    Pitri dish(cfg.width, cfg.height);

    init(dish, t);
    
	for(int i = 0; i < cfg.frames; i++)
	{
		std::cout << "frame: "+std::to_string(i+1) << std::endl;

        canvas.clear();

        auto dishBuffer = dish.getBuffer();

        // Draw the pitri dish to the buffer
        for (int ii = 0; ii < dishBuffer.size(); ii++)
        {
            if (dishBuffer[ii] > 0)
            {
                canvas.draw(ii);
            }
        }
        int living = dish.nextGen();

        auto frame = canvas.getBuffer();

        // Delay the first generation
        int delay = i == 0 ? cfg.delay * 4 : cfg.delay;
		GifWriteFrame(&g, frame.data(), cfg.width, cfg.height, delay);
        if (living < 1){
            // all are dead
            std::cout << "!!!Population Death!!!" << std::endl;
            break;
        }
	}

	GifEnd(&g);

	return 0;
}
