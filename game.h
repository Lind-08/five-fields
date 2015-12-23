#ifndef GAME_H
#define GAME_H
#include <vector>
#include <map>
#include "point.h"

using namespace std;

typedef pair<int,int> coord;

class game
{
    int _width;
    int _height;
    char _emptysymbol = '.';
    char _player1symbol = '#';
    char _player2symbol = '@';
    bool currentPlayer;
    vector<point*> points;
    bool checkDirection(coord new_c, point* p);
public:
    game(int width, int height);
    void drawGameMap();
    coord getPlayerStep();
    void isAccessiableStep(coord new_c, point* p);
    void isAccessiableHop(coord new_c, point* p);
    void changeCoordinates(coord new_c, point* p);
    int checkGameState();
};

#endif // GAME_H
