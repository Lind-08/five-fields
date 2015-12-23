#ifndef POINT_H
#define POINT_H
#include <iostream>

class point
{
    int _x;
    int _y;
    int _player_id;
    char _symbol;
public:
    point(int x, int y, char symbol, int player_id);
    void draw();
};

#endif // POINT_H
