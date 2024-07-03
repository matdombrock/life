#pragma once
#include <vector>
class MathTools
{
public:
    template <typename T=double>
    static double avgVec(std::vector<T> vec)
    {
        if(vec.size() == 0)
        {
            return 0;
        }
        double sum = 0;
        for(auto item : vec)
        {
            sum += item;
        }
        return sum / vec.size();
    }
    template <typename T=double>
    static T sumVec(std::vector<T> vec)
    {
        double sum = 0;
        for(auto item : vec)
        {
            sum += item;
        }
        return sum;
    }
    // Returns the smaller of 2 values
    template <typename T=double>
    static T min(T a, T b)
    {
        return a < b ? a : b;
    }
    // Returns the larger of 2 values
    template <typename T=double>
    static T max(T a, T b)
    {
        return a > b ? a : b;
    }
    // Returns the smallest number in a vector
    template <typename T=double>
    static T minVec(std::vector<T> vec)
    {
        T out;
        for (T item : vec)
        {
            out = min(item, out);
        }
        return out;
    }
    // Returns the largest number in a vector
    template <typename T=double>
    static T maxVec(std::vector<T> vec)
    {
        T out;
        for (T item : vec)
        {
            out = max(item, out);
        }
        return out;
    }
};