#include "game.h"

game::game(int cellsCount)
{
    finished = false;
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

bool game::isAccessiableStep(pair<coord, coord> player_step)
{
    int delta_x = abs(player_step.first.first - player_step.second.first);
    int delta_y = abs(player_step.first.second - player_step.second.second);
    if ((delta_x + delta_y) > 1)
        return false;
    try
    {
        points->at(player_step.second);
    }
    catch (...)
    {
        return true;
    }
    return false;
}

bool game::isAccessiableHop(pair<coord, coord> player_step)
{
    int delta_x = abs(player_step.first.first - player_step.second.first);
    int delta_y = abs(player_step.first.second - player_step.second.second);
    if ((delta_x + delta_y) > 2)
        return false;
    coord c_temp(player_step.first);
    if (delta_x > delta_y)
        if (player_step.first.first > player_step.second.first)
            c_temp.first -= 1;
        else
            c_temp.first += 1;
    else
        if (player_step.first.second > player_step.second.second)
            c_temp.second -= 1;
        else
            c_temp.second += 1;
    try
    {
        point *p = points->at(c_temp);
        if (!p->player_id() != currentPlayer)
           return false;
        else
        {
            if (isAccessiableStep(pair<coord,coord>(c_temp,player_step.second)))
                return true;
            else return false;
        }
    }
    catch(...)
    {
        return false;
    }
}

bool game::isCanFindPath(pair<coord, coord> player_step)
{
    coord current_p = player_step.first;
    stack<pair<int,coord>> path;
    int dir = 0;
    coord new_p(current_p);
    while (true)
    {
        switch (dir)
        {
        case 0:
            new_p.second += 2; break;
        case 1:
            new_p.first += 2;
           break;
        case 2:
            new_p.second -= 2; break;
        case 3:
            new_p.first -= 2; break;
        default:
           {
                if (current_p == player_step.first)
                    return false;
                pair<int,coord> tmp = path.top();
                path.pop();
                dir = tmp.first + 1;
                current_p = tmp.second;
                new_p = tmp.second;
                continue;
            }
        }
        if (new_p != path.top().second)
        {
            if (isAccessiableHop(pair<coord,coord>(current_p,new_p)))
            {
                if (new_p == player_step.first)
                {
                    pair<int,coord> tmp = path.top();
                    path.pop();
                    dir = tmp.first + 1;
                    current_p = tmp.second;
                    continue;
                }
                if (new_p == player_step.second)
                    return true;
                else
                {
                    path.push(pair<int,coord>(dir,current_p));
                    current_p = new_p;
                    dir = 0;
                    continue;
                }
            }
        }
        dir += 1;
        new_p = current_p;
    }
}

void drawEmptyPoint()
{
    cout.width(3);
    cout << ".";
}

bool game::checkPointPlayer(coord c)
{
    try
    {
        if (points->at(c)->player_id() == currentPlayer)
            return true;
    }
    catch (...)
    {
        return false;
    }
    return false;
}

bool game::checkGameState()
{
    int res = calcCellsCountInField(currentPlayer);
    if (res == _cellsCount)
        return true;
    else
        return false;
}

int game::calcCellsCountInField(bool player_id)
{
    int count = 0;
    int first_x = player_id ? _width : _width*2;
    int first_y = player_id ? _height*2 : _height;
    for (int i = first_x; i < first_x + _width; i++)
        for (int j = first_y; j < first_y + _height; j++)
        {
            try
            {
                if (points->at(coord(i,j))->player_id() == player_id)
                    count++;
            }
            catch (...)
            {
                continue;
            }
        }
    return count;
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
        point* p = points->at(player_step.first);
        p->step(player_step.second);
        points->erase(points->find(player_step.first));
        points->insert(pair<coord,point*>(player_step.second,p));
        if (checkGameState())
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

void game::finishGame()
{
    drawGameMap();
    cout << "Player" << (currentPlayer ? '2' : '1') << " win!" << endl;
    finished = true;
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
    mainLoop();
}

