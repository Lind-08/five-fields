#ifndef COORDINATE_EQUAL_PRED_H
#define COORDINATE_EQUAL_PRED_H
#include "definitions.h"

class coordinate_equal_pred
{
    coord _coordinates;
public:
    coordinate_equal_pred(int x, int y)
    {
        _coordinates.first = x;
        _coordinates.second = y;
    }
    bool operator()(point* p)
    {
        if (p->x() == _coordinates.first && p->y() == _coordinates.second)
            return true;
        else
            return false;
    }
};


#endif // COORDINATE_SEARCHER_H

