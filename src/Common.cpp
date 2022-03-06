#include "Common.h"

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
        return 1 << val;
    }

}