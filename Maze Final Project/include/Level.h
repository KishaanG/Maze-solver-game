class Enemy;
class Player;
#include "Item.h"
#include <iostream>
using namespace std;
#ifndef LEVEL_H
#define LEVEL_H

const int size = 20;

/// ============= Walls
const char VRT = '\272'; // ║
const char TPR = '\273'; // ╗
const char TPL = '\311'; // ╔
const char BML = '\310'; // ╚
const char BMR = '\274'; // ╝
//const char MDL = '\271'; // ╣
const char HRZ = '\315'; // ═
const int numOfWallTypes = 6;
const char wallTypes[numOfWallTypes] = {VRT, TPR, TPL, BML, BMR, HRZ};

/// ============= Extra characters
const char PLY = '\352'; // Ω
const char SPC = ' ';
const char WKD = '.';
const char ENM = '\353'; // δ
const char DOR = '\333'; // █
const char ITM = '\354'; //

class Level
{
    private:
        int endXPos;
        int endYPos;
        int startXPos;
        int startYPos;
        Enemy *enemiesInLevel[10];
        Item *itemsInLevel[5];

    public:
        Level(); // Default Constructor
        Level(int, int, int, int, char[size][size], Enemy*[10], Item*[5]); // Custom Constructor
		virtual ~Level(); // Destructor
        int getEndXPos();
        int getEndYPos();
        int getStartXPos();
        int getStartYPos();
        void display();
        char maze[size][size];
        bool checkAllEnemiesDefeated();
        void enemyKilled(int, int);
        Enemy* getEnemy(int, int);
        void setLevel(Player*);
        Item **getItemsInLevel();
};

#endif // LEVEL_H
