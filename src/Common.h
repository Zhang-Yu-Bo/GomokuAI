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
        bool operator<(const Pos &cmp) {
            return (this->rowY < cmp.rowY) || (this->rowY == cmp.rowY && this->colX < cmp.colX);
        }
    } Pos;

    int Clamp(int val, int min, int max);
    void CopyArray(const int *src, int *&dst, int length);
    int WeightFunction(int val);
}

#endif