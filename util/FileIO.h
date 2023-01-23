/*
Basic file handing
*/

#pragma once
#include <iostream>
#include <fstream>
#include <string>

class File
{
public:
    static std::string read(std::string fileName)
    {
        std::string text;
        std::ifstream fileReader(fileName);
        std::string out;
        while(std::getline(fileReader, text))
        {
            out += text;
        }
        fileReader.close();
        return out;
    }
    static void write(std::string fileName, std::string content)
    {
        std::ofstream file(fileName);
        file << content;
        file.close();
    }
};