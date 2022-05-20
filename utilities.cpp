#include "utilities.h"

void swap(Piece& a, Piece& b)
{
    Piece temp = a;
    a = b;
    b = temp;
}

bool bSwap(bool entry)
{
    if (entry) return false;
    return true;
}
