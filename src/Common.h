#ifndef _COMMON_H_
#define _COMMON_H_

namespace Common
{
    const int BLACK = 0;
    const int WHITE = 1;

    typedef struct Pos
    {
    public:
        int rowY;
        int colX;
        Pos(int row, int col)
        {
            this->rowY = row;
            this->colX = col;
        }
    } Pos;

    int Clamp(int val, int min, int max);
    void CopyArray(const int *src, int *&dst, int length);
    int WeightFunction(int val);
}

#endif