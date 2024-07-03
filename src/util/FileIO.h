/*
Basic file handing
*/

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class FileIO
{
public:
    static std::string read(std::string fileName)
    {
        std::ifstream fileReader(fileName);
        std::string out;
        std::string text;
        while(std::getline(fileReader, text))
        {
            out += text + "\r\n";
        }
        fileReader.close();
        return out;
    }
    static std::vector<std::string> readLines(std::string fileName)
    {
        std::ifstream fileReader(fileName);
        std::vector<std::string> out;
        std::string text;
        while(std::getline(fileReader, text))
        {
            out.push_back(text);
        }
        fileReader.close();
        return out;
    }
    static void copy(std::string fileName, std::string fileName2)
    {
        std::ifstream fileReader(fileName);
        std::ofstream file2(fileName2);
        std::string text;
        while(std::getline(fileReader, text))
        {
            file2 << text << std::endl;
        }
        file2.close();
        fileReader.close();
    }
    static void write(std::string fileName, std::string content)
    {
        std::ofstream file(fileName);
        file << content;
        file.close();
    }
};