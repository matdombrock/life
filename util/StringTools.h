#pragma once
#include <string>
#include <vector>
#include <algorithm>

class StringTools
{
public:
    static std::string removeSpaces(std::string line)
    {
        // clear spaces
        std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
        line.erase(end_pos, line.end());
        return line;
    }
    template <typename T=double>
    static std::string vecToString(std::vector<T> vec)
    {
        std::string out;
        for (int i = 0; i < vec.size(); i++)
        {
            out += std::to_string(vec[i]);
            if (i + 1 < vec.size())
            {
                out += ", ";
            }
        }
        return out;
    }
};