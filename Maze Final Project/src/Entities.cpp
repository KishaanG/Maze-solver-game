#include <iostream>
#include "Entities.h"
#include "Player.h"
#include "Moves.h"
using namespace std;

Entities::Entities()
{
    //ctor
    name = "";
    type = "";
    img = 'X';
    xPos = 0;
    yPos = 0;
    initialHealth = 100;
    health = 100;
    for (int i=0; i<4; i++)
    {
        moves[i] = nullptr;
    }
}

Entities::Entities(string _name, string _type, int _xPos, int _yPos, char _img, int _health) : Object(_xPos, _yPos, _img, _name)
{
    //custom ctor
    type = _type;
    initialHealth = _health;
    health = _health;
    for (int i=0; i<4; i++)
    {
        moves[i] = nullptr;
    }
}

Entities::~Entities()
{
    //dtor
}

bool Entities::canMoveInDirection(Level level, char direction)
{ /// Returns whether or not the player in move in the desired direction
    char nextPos = nextInDirection(level, direction);
    bool nextNotWall = true;
    for (int i=0; i<numOfWallTypes; i++)
    {
        if (nextPos == wallTypes[i])
        { /// Checks if the next position is a wall
            nextNotWall = false;
            i=numOfWallTypes;
        }
    }
    if (nextNotWall)
    {
        if (nextPos == DOR and !level.checkAllEnemiesDefeated())
        { /// Checks if the next position is a door and if all the enemies are defeated
            return false;
        }
        return true;
    }
    else
    {
        return false;
    }
}

char Entities::nextInDirection(Level level, char direction)
{ /// Returns the character of the next position in the maze
    char nextPos = ' ';
    if (direction == 'w')
    {
        nextPos = level.maze[yPos-1][xPos];
    }
    else if (direction == 's')
    {
        nextPos = level.maze[yPos+1][xPos];
    }
    else if (direction == 'a')
    {
        nextPos = level.maze[yPos][xPos-1];
    }
    else if (direction == 'd')
    {
        nextPos = level.maze[yPos][xPos+1];
    }
    return nextPos;
}

string Entities::getType()
{
    return type;
}

void Entities::setType(string _type)
{
    type = _type;
    return;
}

int Entities::getHealth()
{
    return health;
}

void Entities::setHealth(int _health)
{
    health = _health;
    return;
}

int Entities::getInitialHealth()
{
    return initialHealth;
}

void Entities::addMove(Moves *moveAdded)
{ /// Adds a new move to the end of the moves list
    if (moveAdded == nullptr)
    {
        return;
    }
    for (int i=0; i<4; i++)
    {
        if (moves[i] == nullptr)
        {
            moves[i] = moveAdded;
            return;
        }
    }
    return;
}

int Entities::getNumOfMoves()
{ /// Returns the number of moves the Entities have
    int numOfMoves = 0;
    for (int i=0; i<4; i++)
    {
        if (moves[i] != nullptr)
        {
            numOfMoves++;
        }
    }
    return numOfMoves;
}

Moves** Entities::getMoves()
{
    return moves;
}

void Entities::displayHealth()
{
    for (int i=1; i<=health; i+=2)
    { /// Displays bars representing the Entities' health
        cout << '\333';
    }
    for (int i=health+1; i<initialHealth; i+=2)
    {
        cout << " ";
    }
    cout << "|";
    return;
}

