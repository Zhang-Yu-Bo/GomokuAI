#include "Common.h"
#include <iostream>

namespace Common
{

    int Clamp(int val, int min, int max)
    {
        val = val < min ? min : val;
        val = val > max ? max : val;
        return val;
    }

    void CopyArray(const int* src, int*& dst, int length) {
        for (int i = 0; i < length; i++)
            dst[i] = src[i];
    }

    int WeightFunction(int val) {
        int base = 10; // 1 10 100 1000 
        int score = 1;
        for (int i = 0; i < val; i++)
            score *= base;
        return score;
    }

}