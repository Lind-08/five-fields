#include "game.h"

game::game(int cellsCount)
{
    _width = cellsCount;
    _height = cellsCount;
    _cellsCount = cellsCount * cellsCount;
    currentPlayer = false;
    points = new map<coord,point*>();
    for (int i = _height; i < (_height * 2); i++)
        for (int j = 0; j < _width; j++)
        {
            point *p = new point(j,i,_player1symbol,false);
            coord c(j,i);
            points->insert(pair<coord,point*>(c,p));
        }
    for (int i = _height; i < (_height * 2); i++)
        for (int j = 0; j <_width; j++)
        {
            point *p = new point(i,j,_player2symbol,true);
            coord c(i,j);
            points->insert(pair<coord,point*>(c,p));
        }
}

bool game::checkAllowCoord(int x, int y)
{
    if ((x >= _width && x < 2*_width) || (y >= _height && y < 2*_height))
        return true;
    else
        return false;
}

void drawEmptyPoint()
{
    cout.width(3);
    cout << ".";
}

bool game::checkPointPlayer(coord c)
{
    if (points->at(c)->player_id() == currentPlayer)
        return true;
    else
        return false;
}

int game::calcCellsCountInField(bool player_id)
{
    return 0;
}

void game::drawGameMap()
{
    cout << "  ";
    for (int i = 0; i < _width * 3; i++)
    {
        std::cout.width(3);
        cout << i;
    }
    cout << endl;
    for (int i = 0; i < _height *3; i++)
    {
        cout.width(2);
        cout << i;
        for (int j = 0; j < _width * 3; j++)
        {
            if (checkAllowCoord(j,i))
            {
                point *p;
                try
                {
                    p = points->at(coord(j,i));
                }
                catch (...)
                {
                    drawEmptyPoint();
                    continue;
                };
                p->draw();
            }
            else
                cout << "   ";
        }
        cout << endl;
    }
    cout << "Player 1: " << _player1symbol << " Player 2: " << _player2symbol << endl;
    cout << "Cells in players field: Player 1 - " << calcCellsCountInField(false) << " Player 2 - " << calcCellsCountInField(true) << endl;
}

pair<coord,coord> game::getPlayerStep()
{
    coord point_pos, new_pos;
    cout << "Player" << (currentPlayer ? '2' : '1') << " step" << endl;
    cout << "Insert point position (x): ";
    cin >> point_pos.first;
    cout << "(y): ";
    cin >> point_pos.second;
    cout << endl << "Insert new position (x): ";
    cin >> new_pos.first;
    cout << "(y): ";
    cin >> new_pos.second;
    return pair<coord,coord>(point_pos, new_pos);
}

bool game::step(pair<coord,coord> player_step)
{
    if (!checkPointPlayer(player_step.first))
    {
        cout << "Error step. This is not your point." << endl;
        return false;
    }
    if (isAccessiableStep(player_step) || isAccessiableHop(player_step) || isCanFindPath(player_step))
    {
        points->at(player_step.first)->step(player_step.second);
        if (checkGameState() == 1)
        {
            finishGame();
        }
        else
            currentPlayer = !currentPlayer;
        return true;
    }
    else
    {
        cout << "Error step." << endl;
        return false;
    }
}



void game::mainLoop()
{
    while (!finished)
    {
        drawGameMap();
        step(getPlayerStep());
    }
}

void game::startGame()
{
    drawGameMap();
}

