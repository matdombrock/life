#pragma once
class Cfg
{
public:
    const char * fileName = "out/life";
    int delay = 16;
    int frames = 64;
    int width = 256;
    int height = 256;
    int scale = 4;
    char ruleSet[4] = {'d','s','t','d'};// game of life = {'d','s','t','d'}
};