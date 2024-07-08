/**

    Author: Kishaan Gidda
    Description: Maze game including a maze auto solver.
    Last modified: June 19, 2024

**/

/// ============================================================ Pre-processor coommands

#include <iostream>
#include <windows.h> /// For Sleep function
#include <conio.h> /// For _getch function
#include <limits> /// For cin.ignore
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Moves.h"
#include "Item.h"
#include "Object.h"
#include "Healing.h"
#include "Damaging.h"
using namespace std;

/// ============================================================ Protoypes

/// =========== Generic functions
void keyToContinue();
int menu(string, string[], int, string);
void learnNewMove(Player*, Moves*, Moves*, Moves*);

/// =========== Level functions
void introMenu(Player*);
void firstLevel(Player*);
void secondLevel(Player*);
void thirdLevel(Player*);
int outro();

/// ============================================================ Definitions

/// ==================================== keyToContinue
void keyToContinue()
{ /// Generic key to continue function
	cout << "Type any key to continue." << endl;
	_getch();
	return;
}

/// ==================================== Menu
int menu(string prompt, string options[], int numberOfOptions, string errorMsg)
{
	int response; /// This is a generic menu function to display questions and get a user response
	do {
		cout << prompt << endl;
		for (int i = 0; i < numberOfOptions; i++) {
			cout << i + 1 << ") " << options[i] << endl; /// Displays the options
		}
		cin >> response;
		if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << errorMsg << endl;
            keyToContinue();
            system("cls");
        }
		else if (response < 1 or response > numberOfOptions)
        {
			cout << errorMsg << endl; /// Displays error messsage for invalid inputs
			keyToContinue();
			system("cls");
		}
	} while (response < 1 or response > numberOfOptions);
	return response;
}

/// ==================================== learnNewMove
void learnNewMove(Player *_player, Moves *_move1, Moves *_move2, Moves *_move3)
{ /// Interface providing options to the user of 3 moves they can learn
    string moveOptions[3] = {_move1->getName()+" | "+to_string(_move1->getDamage())+" dmg | "+to_string(_move1->getInitialUses())+" uses", _move2->getName()+" | "+to_string(_move2->getDamage())+" dmg | "+to_string(_move2->getInitialUses())+" uses", _move3->getName()+" | "+to_string(_move3->getDamage())+" dmg | "+to_string(_move3->getInitialUses())+" uses"};
    int moveChoice = menu("You can learn a new move!", moveOptions, 3, "Please enter a valid input."); /// Gets the user's choice
    if (moveChoice == 1) /// Adds the chosen move to the player
    {
        _player->addMove(_move1);
    }
    else if (moveChoice == 2)
    {
        _player->addMove(_move2);
    }
    else
    {
        _player->addMove(_move3);
    }
    system("cls");
    return;
}

/// ==================================== introMenu
void introMenu(Player *_mainPlayer)
{
    cout << "Welcome brave soldier to the king's castle, but first. ";
    string options[2] = {"Yes", "No"};
    string name;
    do
    { /// Gets the players name
        cout << "What's your name?" << endl;
        cin >> name;
        system("cls");
    }while (menu("Your name is " + name + ", is that right?", options, 2, "Please enter a valid input.") == 2);
    _mainPlayer->setName(name);
    system("cls");

    cout << "You're here to save the palace from the army that took it over. The enemy guards can be either fire, water, or ground type.\nWater moves hit harder against fire types.\nFire moves hit harder against ground types.\nGround moves hit harder against water types." << endl;

    string typeOptions[3] = {"Water", "Fire", "Ground"};
    int userTypeChoice = menu("Which type are you?", typeOptions, 3, "Please enter a valid input."); /// Gets the user's selected type

    if (userTypeChoice ==  1)
    {
        _mainPlayer->setType("Water");
    }
    else if (userTypeChoice == 2)
    {
        _mainPlayer->setType("Fire");
    }
    else
    {
        _mainPlayer->setType("Ground");
    }
    system("cls");
    cout << "The '" << PLY << "' character is you, the '" << ITM << "' characters are items, and the '" << ENM << "' characters are enemies.\nClick 'p' if you ever want an autosolver to take over to beat the level." << endl;
    cout << "Now hury up, get in there and get rid of the enemies!" << endl;
    keyToContinue();
    system("cls");
    return;
}

/// ==================================== firstLevel
void firstLevel(Player *_mainPlayer)
{
    char maze[size][size] = {
    {TPL,DOR,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,TPR},
    {VRT,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT},
    {VRT,SPC,BML,HRZ,HRZ,HRZ,HRZ,HRZ,SPC,SPC,SPC,SPC,SPC,SPC,SPC,TPL,HRZ,HRZ,SPC,VRT},
    {VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,TPL,HRZ,TPR,SPC,SPC,SPC,VRT,SPC,SPC,SPC,VRT},
    {VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,BML,HRZ,HRZ,HRZ,BMR,SPC,SPC,SPC,VRT},
    {VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT},
    {VRT,SPC,SPC,SPC,TPL,HRZ,SPC,SPC,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT},
    {VRT,SPC,SPC,SPC,VRT,SPC,SPC,SPC,SPC,BML,HRZ,HRZ,HRZ,HRZ,TPR,SPC,SPC,SPC,SPC,VRT},
    {VRT,SPC,SPC,SPC,VRT,SPC,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,BML,HRZ,HRZ,HRZ,HRZ,VRT},
    {VRT,HRZ,HRZ,HRZ,BMR,SPC,SPC,VRT,SPC,TPL,HRZ,HRZ,TPR,SPC,SPC,SPC,SPC,SPC,SPC,VRT},
    {VRT,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,VRT,SPC,SPC,BML,HRZ,HRZ,HRZ,HRZ,TPR,SPC,VRT},
    {VRT,SPC,TPL,HRZ,HRZ,HRZ,HRZ,BMR,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,VRT},
    {VRT,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT},
    {VRT,SPC,VRT,SPC,SPC,SPC,TPL,HRZ,HRZ,HRZ,HRZ,TPR,SPC,TPL,HRZ,HRZ,HRZ,TPR,SPC,VRT},
    {VRT,SPC,BML,HRZ,HRZ,SPC,VRT,SPC,SPC,SPC,SPC,VRT,SPC,VRT,SPC,SPC,SPC,VRT,SPC,VRT},
    {VRT,SPC,SPC,SPC,SPC,SPC,VRT,SPC,HRZ,HRZ,SPC,VRT,SPC,VRT,SPC,VRT,SPC,VRT,SPC,VRT},
    {VRT,SPC,HRZ,HRZ,TPR,SPC,VRT,SPC,SPC,SPC,SPC,VRT,SPC,VRT,SPC,SPC,SPC,VRT,SPC,VRT},
    {VRT,SPC,SPC,SPC,VRT,SPC,BML,HRZ,HRZ,HRZ,SPC,BML,HRZ,BMR,SPC,HRZ,HRZ,BMR,HRZ,VRT},
    {VRT,SPC,SPC,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT},
    {BML,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,BMR}
    }; /// This is the maze
    bool finishedMaze = false;
    int startingXPos = 18; /// Coordinates for the start of the maze
    int startingYPos = 18;
    int endXPos = 1; /// Coordinates for the end of the maze
    int endYPos = 0;

    Healing healingPotion(7, 5, ITM, "Potion", 40); /// Initializes the Items available in the level
    Damaging throwingStar(12,16,ITM,"Throwing Star", 55);
    Item *itemList[5] = {&healingPotion,&throwingStar,nullptr,nullptr,nullptr};

    Moves fireEnemyMove("Ember", 10, "Fire", 10000); /// Initializes the Moves the enemies will use
    Moves waterEnemyMove("Water Gun", 10, "Water", 10000);
    Moves groundEnemyMove("Mud Shot", 10, "Ground", 10000);

    Enemy waterEnemy("Guard", "Water", 1, 3, ENM, 60); /// Initializes the enemies in the maze
    Enemy fireEnemy("Guard", "Fire", 12, 12, ENM, 60);
    Enemy groundEnemy("Guard", "Ground", 12, 5, ENM, 60);

    waterEnemy.addMove(&waterEnemyMove); /// Adds the moves to the enemies
    fireEnemy.addMove(&fireEnemyMove);
    groundEnemy.addMove(&groundEnemyMove);

    Enemy *enemyList[10] = {&waterEnemy,&fireEnemy,&groundEnemy,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr};

    _mainPlayer->setXPos(startingXPos);
    _mainPlayer->setYPos(startingYPos);

    Level firstLevel(startingXPos, startingYPos, endXPos, endYPos, maze, enemyList, itemList); /// Initializes the Level
    firstLevel.setLevel(_mainPlayer);
    firstLevel.display();

    char moveDirection = ' ';
    while (!finishedMaze)
    { /// Loop that runs until the Level is finished
        moveDirection = _getch(); /// Gets the user's direction chosen
        if (moveDirection == 'p')
        { /// Runs the autoMover if the user clicks 'p'
            _mainPlayer->autoMover(&firstLevel);
            finishedMaze = true;
        }
        else
        {
            finishedMaze = _mainPlayer->move(moveDirection, &firstLevel, false);
        }
        system("cls");
        firstLevel.display(); /// Displays the Level
    }
    system("cls");
    return;
}

/// ==================================== secondLevel
void secondLevel(Player *_mainPlayer)
{
    char maze[size][size] = {
    {TPL,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,DOR,HRZ,HRZ,TPR},
    {VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,VRT,SPC,VRT},
    {VRT,SPC,SPC,SPC,SPC,HRZ,HRZ,TPR,SPC,TPL,TPR,SPC,SPC,SPC,SPC,VRT,SPC,VRT,SPC,VRT},
    {VRT,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,VRT,VRT,SPC,TPL,HRZ,HRZ,BMR,SPC,VRT,SPC,VRT},
    {VRT,SPC,SPC,TPL,HRZ,HRZ,HRZ,VRT,SPC,BML,BMR,SPC,VRT,SPC,SPC,SPC,SPC,VRT,SPC,VRT},
    {VRT,SPC,SPC,VRT,SPC,SPC,SPC,VRT,SPC,SPC,SPC,SPC,VRT,SPC,TPL,HRZ,HRZ,BMR,SPC,VRT},
    {VRT,SPC,SPC,BML,HRZ,TPR,SPC,BML,HRZ,HRZ,HRZ,HRZ,BMR,SPC,VRT,SPC,SPC,SPC,SPC,VRT},
    {VRT,SPC,SPC,SPC,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,VRT,SPC,SPC,VRT},
    {VRT,SPC,HRZ,TPR,SPC,BML,HRZ,HRZ,SPC,TPR,SPC,HRZ,HRZ,HRZ,BMR,SPC,VRT,SPC,SPC,VRT},
    {VRT,SPC,SPC,BML,TPR,SPC,SPC,SPC,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,SPC,VRT},
    {VRT,SPC,SPC,SPC,VRT,SPC,SPC,SPC,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,SPC,VRT},
    {VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,SPC,SPC,SPC,VRT,SPC,SPC,TPL,HRZ,VRT},
    {VRT,SPC,TPL,HRZ,HRZ,HRZ,TPR,SPC,TPL,HRZ,HRZ,HRZ,TPR,SPC,BML,TPR,SPC,VRT,SPC,VRT},
    {VRT,SPC,VRT,SPC,SPC,SPC,VRT,SPC,VRT,SPC,SPC,SPC,VRT,SPC,SPC,VRT,SPC,VRT,SPC,VRT},
    {VRT,HRZ,VRT,SPC,VRT,SPC,VRT,SPC,VRT,SPC,VRT,SPC,VRT,SPC,SPC,VRT,SPC,VRT,SPC,VRT},
    {VRT,SPC,VRT,SPC,VRT,SPC,VRT,SPC,VRT,SPC,VRT,SPC,BML,HRZ,HRZ,BMR,SPC,VRT,SPC,VRT},
    {VRT,SPC,SPC,SPC,SPC,SPC,VRT,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,VRT},
    {VRT,SPC,BML,HRZ,HRZ,HRZ,BMR,HRZ,BMR,SPC,TPL,HRZ,HRZ,HRZ,HRZ,HRZ,SPC,BML,HRZ,VRT},
    {VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,BML,HRZ,BMR,SPC,SPC,SPC,SPC,SPC,SPC,VRT},
    {BML,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,BMR}
    };
    bool finishedMaze = false;
    int startingXPos = 2;
    int startingYPos = 18;
    int endXPos = 16;
    int endYPos = 0;

    Healing superPotion(10, 13, ITM, "Super Potion", 60);
    Healing potion(4, 13, ITM, "Potion", 50);
    Healing maxPotion(1, 5, ITM, "Max Potion", 100);
    Damaging grenade(12,10,ITM,"Grenade", 65);
    Item *itemList[5] = {&superPotion,&grenade,&potion,&maxPotion,nullptr};

    Enemy waterSoldier("Soldier", "Water", 16, 2, ENM, 85);
    Enemy fireGuard("Guard", "Fire", 16, 13, ENM, 75);
    Enemy groundGuard("Guard", "Ground", 6, 1, ENM, 75);
    Enemy waterGuard("Guard", "Water", 6, 18, ENM, 60);

    Moves waterEnemyMove("Waterfall", 30, "Water", 10000);
    Moves fireEnemyMove("Blast Burn", 30, "Fire", 10000);
    Moves groundEnemyMove("Earth Power", 30, "Ground", 10000);
    Moves waterSpecialMove("Surf", 40, "Water", 1);
    Moves fireSpecialMove("Flare Blitz", 40, "Fire", 1);
    Moves groundSpecialMove("Fissure", 40, "Ground", 1);


    waterSoldier.addMove(&waterEnemyMove);
    waterSoldier.addMove(&waterSpecialMove);
    waterGuard.addMove(&waterEnemyMove);
    fireGuard.addMove(&fireEnemyMove);
    fireGuard.addMove(&fireSpecialMove);
    groundGuard.addMove(&groundEnemyMove);
    groundGuard.addMove(&groundSpecialMove);

    Enemy *enemyList[10] = {&waterSoldier,&fireGuard,&groundGuard,&waterGuard,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr};

    _mainPlayer->setXPos(startingXPos);
    _mainPlayer->setYPos(startingYPos);

    Level secondLevel(startingXPos, startingYPos, endXPos, endYPos, maze, enemyList, itemList);
    secondLevel.setLevel(_mainPlayer);
    secondLevel.display();

    char moveDirection = ' ';
    while (!finishedMaze)
    {
        moveDirection = _getch();
        if (moveDirection == 'p')
        {
            _mainPlayer->autoMover(&secondLevel);
            finishedMaze = true;
        }
        else
        {
            finishedMaze = _mainPlayer->move(moveDirection, &secondLevel, false);
        }
        system("cls");
        secondLevel.display();
    }
    system("cls");
    return;
}

/// ==================================== thirdLevel
void thirdLevel(Player *_mainPlayer)
{
    char maze[size][size] = {
    {TPL,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,DOR,HRZ,HRZ,TPR},
    {VRT,SPC,SPC,SPC,SPC,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,VRT,SPC,VRT},
    {VRT,SPC,SPC,SPC,SPC,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,VRT,SPC,VRT},
    {VRT,SPC,SPC,SPC,SPC,SPC,VRT,SPC,SPC,SPC,SPC,TPL,HRZ,HRZ,HRZ,BMR,SPC,VRT,SPC,VRT},
    {VRT,SPC,TPL,HRZ,HRZ,HRZ,BMR,SPC,SPC,SPC,SPC,VRT,SPC,SPC,SPC,SPC,SPC,VRT,SPC,VRT},
    {VRT,SPC,VRT,SPC,SPC,SPC,SPC,SPC,TPL,HRZ,HRZ,BMR,SPC,HRZ,HRZ,HRZ,TPR,SPC,SPC,VRT},
    {VRT,SPC,VRT,TPL,HRZ,HRZ,TPR,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,SPC,VRT},
    {VRT,SPC,VRT,VRT,SPC,SPC,VRT,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,SPC,VRT},
    {VRT,SPC,BML,BMR,SPC,SPC,VRT,SPC,VRT,SPC,SPC,SPC,SPC,VRT,SPC,SPC,VRT,SPC,SPC,VRT},
    {VRT,SPC,SPC,SPC,SPC,SPC,VRT,SPC,BML,HRZ,HRZ,HRZ,HRZ,BMR,SPC,SPC,VRT,SPC,SPC,VRT},
    {VRT,SPC,HRZ,TPR,SPC,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,SPC,VRT},
    {VRT,SPC,SPC,VRT,SPC,SPC,VRT,SPC,HRZ,HRZ,HRZ,HRZ,HRZ,TPR,SPC,SPC,VRT,SPC,SPC,VRT},
    {VRT,SPC,SPC,VRT,SPC,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,SPC,VRT,SPC,SPC,VRT},
    {VRT,SPC,SPC,VRT,SPC,SPC,VRT,SPC,SPC,SPC,VRT,SPC,TPL,BMR,SPC,TPL,BMR,SPC,SPC,VRT},
    {VRT,SPC,SPC,VRT,SPC,SPC,VRT,SPC,SPC,SPC,VRT,SPC,VRT,SPC,SPC,VRT,SPC,SPC,SPC,VRT},
    {VRT,SPC,SPC,VRT,SPC,SPC,BML,HRZ,HRZ,HRZ,BMR,SPC,BML,HRZ,HRZ,BMR,SPC,TPL,HRZ,VRT},
    {VRT,SPC,SPC,VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,VRT},
    {VRT,HRZ,HRZ,HRZ,HRZ,SPC,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,TPR,SPC,VRT,SPC,VRT},
    {VRT,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,VRT,SPC,SPC,SPC,VRT},
    {BML,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,HRZ,BMR}
    };
    bool finishedMaze = false;
    int startingXPos = 16;
    int startingYPos = 18;
    int endXPos = 16;
    int endYPos = 0;

    Healing superPotion1(18, 16, ITM, "Super Potion", 60);
    Healing superPotion2(16, 14, ITM, "Super Potion", 60);
    Healing superPotion3(18, 12, ITM, "Super Potion", 60);
    Healing maxPotion(11, 12, ITM, "Max Potion", 100);
    Damaging gun(6,16,ITM,"Gun", 85);
    Item *itemList[5] = {&superPotion1,&gun,&superPotion2,&maxPotion,&superPotion3};

    Enemy waterSoldier("Soldier", "Water", 5, 18, ENM, 85);
    Enemy fireSoldier("Soldier", "Fire", 8, 13, ENM, 85);
    Enemy groundSoldier("Soldier", "Ground", 4, 2, ENM, 85);
    Enemy enemyKing("King", "", 16, 2, ENM, 100);

    Moves kingWaterMove("Wave Charge", 85, "Water", 1);
    Moves waterEnemyMove("Water Pulse", 45, "Water", 10000);
    Moves specialWaterMove("Tsunami", 60, "Water", 1);
    waterSoldier.addMove(&waterEnemyMove);
    waterSoldier.addMove(&specialWaterMove);

    Moves kingFireMove("Flame Charge", 85, "Fire", 1);
    Moves specialFireMove("Flamethrower", 60, "Fire", 1);
    Moves fireEnemyMove("Fire Breath", 45, "Fire", 10000);
    fireSoldier.addMove(&fireEnemyMove);
    fireSoldier.addMove(&specialFireMove);

    Moves kingGroundMove("Earth Charge", 85, "Ground", 1);
    Moves groundEnemyMove("Mud Bomb", 45, "Ground", 10000);
    Moves specialGroundMove("Earthquake", 60, "Ground", 1);
    groundSoldier.addMove(&groundEnemyMove);
    groundSoldier.addMove(&specialGroundMove);

    if (_mainPlayer->getType() == "Water")
    {
        enemyKing.setType("Water");
        enemyKing.addMove(&waterEnemyMove);
        enemyKing.addMove(&kingWaterMove);
    }
    else if (_mainPlayer->getType() == "Fire")
    {
        enemyKing.setType("Fire");
        enemyKing.addMove(&fireEnemyMove);
        enemyKing.addMove(&kingFireMove);
    }
    else
    {
        enemyKing.setType("Ground");
        enemyKing.addMove(&groundEnemyMove);
        enemyKing.addMove(&kingGroundMove);
    }

    Enemy *enemyList[10] = {&waterSoldier,&fireSoldier,&groundSoldier,&enemyKing,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr};

    _mainPlayer->setXPos(startingXPos);
    _mainPlayer->setYPos(startingYPos);

    Level thirdLevel(startingXPos, startingYPos, endXPos, endYPos, maze, enemyList, itemList);
    thirdLevel.setLevel(_mainPlayer);
    thirdLevel.display();

    char moveDirection = ' ';
    while (!finishedMaze)
    {
        moveDirection = _getch();
        if (moveDirection == 'p')
        {
            _mainPlayer->autoMover(&thirdLevel);
            finishedMaze = true;
        }
        else
        {
            finishedMaze = _mainPlayer->move(moveDirection, &thirdLevel, false);
        }
        system("cls");
        thirdLevel.display();
    }
    system("cls");
    return;
}

int outro()
{
    cout << "You saved the castle!" << endl;
    string options[2] = {"Yes", "No"};
    return menu("Play again?", options, 2, "Please enter a valid input."); /// Gets input if the user wants to restart the game
}

int main()
{
    do
    {
        system("cls");
        Moves waterMove("Water Jet", 35, "Water", 15); /// Initializes the 3 starter moves the player can learn
        Moves fireMove("Fire Blast", 35, "Fire", 15);
        Moves groundMove("Sand Attack", 35, "Ground", 15);

        Player mainPlayer;

        introMenu(&mainPlayer); /// Initializes the main player in this function

        if (mainPlayer.getType() == "Water") /// Decides the starter move for the player depending on their type
        {
            mainPlayer.addMove(&waterMove);
        }
        else if (mainPlayer.getType() == "Fire")
        {
            mainPlayer.addMove(&fireMove);
        }
        else if (mainPlayer.getType() == "Ground")
        {
            mainPlayer.addMove(&groundMove);
        }

        firstLevel(&mainPlayer); /// Runs the first level of the game

        Moves tsunami("Tsunami", 60, "Water", 10); /// Initializes 3 new moves the player can learn
        Moves flamethrower("Flamethrower", 60, "Fire", 10);
        Moves earthquake("Earthquake", 60, "Ground", 10);

        learnNewMove(&mainPlayer, &tsunami, &flamethrower, &earthquake); /// Offers the player the option of which move to learn

        secondLevel(&mainPlayer); /// Runs the second level of the game

        Moves brine("Brine", 80, "Water", 4);
        Moves sacredFire("Sacred Fire", 80, "Fire", 4);
        Moves fissure("Fissure", 80, "Ground", 4);

        learnNewMove(&mainPlayer, &brine, &sacredFire, &fissure);

        Moves hydroCannon("Hydro Cannon", 90, "Water", 1);
        Moves blueFlare("Blue Flare", 90, "Fire", 1);
        Moves bulldoze("Bulldoze", 90, "Ground", 1);

        learnNewMove(&mainPlayer, &hydroCannon, &blueFlare, &bulldoze);

        thirdLevel(&mainPlayer); /// Runs the third level of the game
    }while(outro() == 1);
    return 0;
}
