#include "Level.h"
#include "Enemy.h"
#include "Player.h"
#include "Moves.h"
#include <conio.h>
#include <iostream>
using namespace std;

Level::Level()
{
    //ctor
    startXPos = 0;
    startYPos = 0;
    endXPos = 1;
    endYPos = 0;
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size; j++)
        {
            maze[i][j] = SPC;
        }
    }
    for (int i=0; i<10; i++)
    {
        enemiesInLevel[i] = nullptr;
    }
    for (int i=0; i<5; i++)
    {
        itemsInLevel[i] = nullptr;
    }
}

Level::Level(int _startXPos, int _startYPos, int _endXPos, int _endYPos, char _maze[size][size], Enemy *_enemiesInLevel[10], Item *_itemsInLevel[5])
{
    //custom ctor
    startXPos = _startXPos;
    startYPos = _startYPos;
    endXPos = _endXPos;
    endYPos = _endYPos;
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size; j++)
        {
            maze[i][j] = _maze[i][j];
        }
    }
    for (int i=0; i<10; i++)
    {
        enemiesInLevel[i] = _enemiesInLevel[i];
    }
    for (int i=0; i<5; i++)
    {
        itemsInLevel[i] = _itemsInLevel[i];
    }
}

Level::~Level()
{
	//dtor
}

int Level::getEndXPos()
{
    return endXPos;
}

int Level::getEndYPos()
{
    return endYPos;
}

int Level::getStartXPos()
{
    return startXPos;
}

int Level::getStartYPos()
{
    return startYPos;
}

void Level::display()
{ /// Displays the 2D array
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size; j++)
        {
            cout << maze[i][j];
        }
        cout << endl;
    }
    return;
}

void Level::enemyKilled(int enemyXPos, int enemyYPos)
{ /// Kills the enemy at a certain position
    Enemy *enemyToKill = getEnemy(enemyXPos, enemyYPos);
    if (enemyToKill != nullptr)
    { /// Sets isAlive to false for the enemy
        enemyToKill->setIsAlive(false);
    }
    return;
}

Enemy* Level::getEnemy(int enemyXPos, int enemyYPos)
{ /// Returns the pointer to an enemy at a certain (x,y) position
    for (int i=0; i<10; i++)
    { /// Iterates through all possible enemies in the Level
        if (enemiesInLevel[i] != nullptr)
        {
            if (enemiesInLevel[i]->getXPos() == enemyXPos and enemiesInLevel[i]->getYPos() == enemyYPos)
            { /// Returns the enemy
                return enemiesInLevel[i];
            }
        }
    }
    return nullptr;
}

bool Level::checkAllEnemiesDefeated()
{ /// Returns whether or not all the enemies in the Level are dead
    for (int i=0; i<10; i++)
    { /// Iterates through all the enemies in the Level and checks if they're dead
        if (enemiesInLevel[i] != nullptr)
        {
            if (enemiesInLevel[i]->getIsAlive())
            { /// If any are alive return false
                return false;
            }
        }
    }
    return true;
}

void Level::setLevel(Player *player)
{ /// Resets the elements of the Level
    if (player == nullptr)
    {
        return;
    }
    for (int i=0; i<10; i++)
    { /// Sets all the enemies in the Level to be alive
        if (enemiesInLevel[i] != nullptr)
        {
            enemiesInLevel[i]->setIsAlive(true);
            enemiesInLevel[i]->setHealth(enemiesInLevel[i]->getInitialHealth());
            maze[enemiesInLevel[i]->getYPos()][enemiesInLevel[i]->getXPos()] = enemiesInLevel[i]->getImg(); /// Places the enemies in the maze
        }
    }
    for (int i=0; i<5; i++)
    { /// Sets all the Items in the Level to be not picked up
        if (itemsInLevel[i] != nullptr)
        {
            itemsInLevel[i]->setIsPickedUp(false);
            maze[itemsInLevel[i]->getYPos()][itemsInLevel[i]->getXPos()] = itemsInLevel[i]->getImg(); /// Places the Items in the maze
        }
    }
    player->setXPos(startXPos); /// Resets the players x and y position
    player->setYPos(startYPos);
    maze[player->getYPos()][player->getXPos()] = player->getImg(); /// Places the player in the maze
    player->setHealth(player->getInitialHealth()); /// Resets the players health to the initial health
    for (int i=0; i<4; i++)
    { /// Restores the uses on the player's moves
        if (player->getMoves()[i] != nullptr)
        {
            player->getMoves()[i]->setUses(player->getMoves()[i]->getInitialUses());
        }
    }
    for (int i=0; i<10; i++)
    { /// Removes all the player's Items
        player->getItems()[i] = nullptr;
    }
    return;
}

Item** Level::getItemsInLevel()
{
    return itemsInLevel;
}
