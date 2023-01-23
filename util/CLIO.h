/*
Basic command line IO
*/

#pragma once
#include <iostream>
#include <string>

class CLIO
{
public:
    template <typename T=std::string>
    static void print(T content, bool lineBreak = true)
    {
        std::cout << content;
        if (lineBreak)
            std::cout << std::endl;
    }
    template <typename T=std::string>
    static T read()
    {
        T input;
        if (std::is_same<T, std::string>::value)
        {
            std::getline(std::cin, input);
        }
        else
        {
            std::cin >> input;
        }
        return input;
    }
    template <typename T=std::string>
    static T ask(std::string question="")
    {
        if(question != "")
        {
            print(question);
        }
        print(">>", false);
        T res = read<T>();
        return res;
    }
};