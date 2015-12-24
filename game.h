#ifndef GAME_H
#define GAME_H
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include "point.h"
#include "coordinate_equal_pred.h"
#include "definitions.h"

using namespace std;


class game
{
    int _width;
    int _height;
    int _cellsCount;
    char _emptysymbol = '.';
    char _player1symbol = '#';
    char _player2symbol = '@';
    bool currentPlayer;
    map<coord,point*> *points;

    bool checkAllowCoord(int x, int y);
    bool isAccessiableStep(pair<coord,coord> player_step);
    bool isAccessiableHop(pair<coord,coord> player_step);
    int checkGameState();
    bool checkPointPlayer(coord);
    pair<coord,coord> getPlayerStep();
    bool step(pair<coord,coord>);
    void changeCoordinates(coord new_c, point* p);

    int calcCellsCountInField(bool player_id);
    void mainLoop();
    void drawGameMap();
public:
    game(int cellsCount);
    ~game()
    {
        delete points;
    }
    void startGame();
};

#endif // GAME_H
