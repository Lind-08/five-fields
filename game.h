#ifndef GAME_H
#define GAME_H
#include <vector>
#include "point.h"

using namespace std;

typedef pair<int,int> coord;

class game
{
    char _emptysymbol = '.';
    char _player1symbol = '#';
    char _player2symbol = '@';
    vector<point> points;
    bool checkDirection(coord new_c, point* p);
public:

    game();
    void drawGameMap();
    void isAccessiableStep(coord new_c, point* p);

};

#endif // GAME_H
