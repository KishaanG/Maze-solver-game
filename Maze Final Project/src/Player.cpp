#include <iostream>
#include <windows.h> /// For Sleep function
#include <conio.h> /// For _getch()
#include "Player.h"
#include "Entities.h"
#include "Stack.h"
#include "Container.h"
#include "Moves.h"
#include <stdlib.h> /// For rand
#include <limits> /// For cin.ignore
using namespace std;

void pushMoves(Stack*, char);

Player::Player() : Entities("", "", 0, 0, PLY, 100)
{
    //ctor
    for (int i=0; i<10; i++)
    {
        items[i] = nullptr;
    }
    numOfItems = 0;
}

Player::Player(string _name, string _type, int _xPos, int _yPos, int _health) : Entities(_name, _type, _xPos, _yPos, PLY, _health)
{
    //custom ctor
    for (int i=0; i<10; i++)
    {
        items[i] = nullptr;
    }
    numOfItems = 0;
}

Player::~Player()
{
    //dtor
}

/// ====================================================================== Player::move
bool Player::move(char keyPressed, Level *_level, bool runningAutoMover)
{
    if (_level == nullptr)
    {
        return true; /// Return true to break the game loop
    }

    char charLeftBehind;

    if(runningAutoMover)
    { /// If running an auto mover, leave bread crumbs of where we've been
        charLeftBehind = WKD;
    }
    else
    { /// Otherwise leave normal spaces
        charLeftBehind = SPC;
    }

    bool canMove = Entities::canMoveInDirection((*_level), keyPressed); /// Determines whether or not we can move in a direction

    bool nextIsEnemy = false;
    char nextInDir = Entities::nextInDirection((*_level), keyPressed); /// Gets the next character in the direction
    if (nextInDir == ENM)
    { /// Checks whether the next character is an enemy
        nextIsEnemy = true;
    }

    if (keyPressed == 'w')
    { /// Moves in the direction if the player can move
        if (canMove)
        {
            _level->maze[yPos-1][xPos] = img; /// Moves the player's character
            _level->maze[yPos][xPos] = charLeftBehind;
            yPos--;
        }
    }
    else if (keyPressed == 'a')
    {
        if (canMove)
        {
            _level->maze[yPos][xPos-1] = img;
            _level->maze[yPos][xPos] = charLeftBehind;
            xPos--;
        }
    }
    else if (keyPressed == 's')
    {
        if (canMove)
        {
            _level->maze[yPos+1][xPos] = img;
            _level->maze[yPos][xPos] = charLeftBehind;
            yPos++;
        }
    }
    else if (keyPressed == 'd')
    {
        if (canMove)
        {
            _level->maze[yPos][xPos+1] = img;
            _level->maze[yPos][xPos] = charLeftBehind;
            xPos++;
        }
    }
    if (nextIsEnemy and !runningAutoMover)
    { /// Start a combat if player runs into an enemy and the auto mover isn't running
        if(combat(_level->getEnemy(xPos, yPos)))
        { /// If player wins the combat, kill the enemy
            _level->enemyKilled(xPos, yPos);
        }
        else
        { /// If player loses the combat, reset the maze
            _level->setLevel(this);
        }
    }
    else if (nextIsEnemy and runningAutoMover)
    { /// If the auto mover is running, kill the enemy
        _level->enemyKilled(xPos, yPos);
    }

    if (nextInDir == ITM)
    { /// Checks if the next character is an Item
        for (int i=0; i<5; i++)
        {
            if (_level->getItemsInLevel()[i] != nullptr)
            {
                if (xPos == _level->getItemsInLevel()[i]->getXPos() and yPos == _level->getItemsInLevel()[i]->getYPos() and _level->getItemsInLevel()[i]->getIsPickedUp() == false)
                {
                    _level->getItemsInLevel()[i]->setIsPickedUp(true);
                    _level->getItemsInLevel()[i]->displayPickedUp(); /// Displays the Item picked up
                    Sleep(1000);
                    for (int j=0; j<10; j++)
                    {
                        if (items[j] == nullptr)
                        { /// Adds the Item to the items list of the player
                            items[j] = _level->getItemsInLevel()[i];
                            numOfItems++;
                            j=10;
                        }
                    }
                    i=5;
                }
            }
        }
    }

    if (xPos == _level->getEndXPos() and yPos == _level->getEndYPos())
    { /// Returns true if the player reached the end x and y pos
        return true;
    }
    return false;
}

/// ====================================================================== Player::combat
bool Player::combat(Enemy *_enemy)
{
    if (_enemy == nullptr)
    { /// Checking for nullptr
        return false;
    }
    int moveChoice = 0;
    int numOfMoves = getNumOfMoves();
    int enemyNumOfMoves = _enemy->getNumOfMoves();
    bool rechooseMove = false;
    bool usedItem = false;

    while (health>0 and _enemy->getHealth()>0)
    {
        do
        {
            usedItem = false;
            combatDisplay((*_enemy)); /// Displays the combat scene
            cin >> moveChoice;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Choose a valid move. " << endl << "Press any key to continue." << endl;
                _getch();
                system("cls");
                rechooseMove = true;
            }
            else if (moveChoice<=0 or moveChoice>numOfMoves+numOfItems)
            { /// Displays error message if the user doesn't select a valid choice
                cout << "Choose a valid move." << endl << "Press any key to continue." << endl;
                _getch();
                system("cls");
                rechooseMove = true;
            }
            else if (moveChoice>numOfMoves and moveChoice<=numOfMoves+numOfItems)
            { /// Checks if the choice was an Item
                system("cls");
                items[moveChoice-1-numOfMoves]->displayUsedItem((*this), (*_enemy));
                items[moveChoice-1-numOfMoves]->useItem(this, _enemy); /// Displays then uses the Item
                usedItem = true;
            }
            else
            { /// Runs if the choice was a valid move
                 if (moves[moveChoice-1]->getUses()<=0)
                 { /// Checks if the move has any uses left
                     cout << "This move is out of uses." << endl << "Press any key to continue." << endl;
                     _getch();
                     system("cls");
                     rechooseMove = true;
                 }
                 else
                 {
                     rechooseMove = false;
                 }
            }
        }while(rechooseMove);

        if (!usedItem)
        { /// Uses then displays the selected move if the user didn't select an Item
            moves[moveChoice-1]->performMove(_enemy);
            system("cls");
            moves[moveChoice-1]->displayMove((*this), (*_enemy));
        }

        Sleep(2000);
        system("cls");
        combatDisplay((*_enemy));
        Sleep(1500);

        if (_enemy->getHealth()>0)
        { /// Checks if the enemy is alive
            moveChoice = rand() % enemyNumOfMoves + 1;
            while (_enemy->getMoves()[moveChoice-1]->getUses() == 0)
            { /// Chooses a random move for the enemy and makes sure it has uses left
                moveChoice = rand() % enemyNumOfMoves + 1;
            }
            _enemy->getMoves()[moveChoice-1]->performMove(this);
            system("cls");
            _enemy->getMoves()[moveChoice-1]->displayMove((*_enemy), (*this)); /// Uses and displays the chosen move
            Sleep(2000);
            system("cls");
        }
    }
    if (health<=0)
    { /// Returns false if the player lost all their health
        return false;
    }
    return true;
}

/// ====================================================================== Player::combatDisplay
void Player::combatDisplay(Enemy _enemy)
{ /// Displays the combat scene
    system("cls");
    cout << _enemy.getType() << " type - " << _enemy.getName() << endl; /// Displays the enemies stats
    cout << "Health: ";
    _enemy.displayHealth(); /// Displays the enemies health bar
    cout << "\n\n\t\t\t\t\t" << _enemy.getImg() << "\n\t\t\t\t------------------\n\n\n";

    cout << "\t\t" << getImg() << "\n\t------------------\n\n";
    cout << "Health: ";
    displayHealth(); /// Displays the player's health bar
    cout << "\n\n";
    int numOfMoves = Entities::getNumOfMoves();
    for (int i=0; i<4; i++)
    { /// Displays the options of moves for the player
        if (moves[i] != nullptr)
        {
            cout << i+1 << ") " << moves[i]->getName() << " | " << moves[i]->getDamage() << " damage | " << moves[i]->getUses() << "/" << moves[i]->getInitialUses() << endl;
        }
    }
    cout << endl;
    for (int i=0; i<10; i++)
    { /// Displays the options of Items for the player
        if (items[i] != nullptr)
        {
            cout << i+1+numOfMoves << ") " << items[i]->getName() << endl;
        }
    }
    return;
}

/// ====================================================================== pushMoves
void pushMoves(Stack *_stack, char lastMove)
{ /// Function that pushes moves to the stack depending on the last move
    if (_stack == nullptr)
    {
        return;
    }
    if (_stack != nullptr)
    {
        if (lastMove == 'w')
        { /// Pushes to the stack with a 'B' before the backtracking move
            _stack->push('s');
            _stack->push('B');
            _stack->push('a');
            _stack->push('d');
            _stack->push('w');
        }
        else if (lastMove == 'a')
        {
            _stack->push('d');
            _stack->push('B');
            _stack->push('s');
            _stack->push('a');
            _stack->push('w');
        }
        else if (lastMove == 'd')
        {
            _stack->push('a');
            _stack->push('B');
            _stack->push('s');
            _stack->push('d');
            _stack->push('w');
        }
        else if (lastMove == 's')
        {
            _stack->push('w');
            _stack->push('B');
            _stack->push('a');
            _stack->push('d');
            _stack->push('s');
        }
    }
    return;
}


/// ====================================================================== Player::autoMover
void Player::autoMover(Level *_level)
{ /// Player auto mover for a given Level
    /// w = Up, a = Left, s = Down, d = Right
    if (_level == nullptr)
    {
        return;
    }
    Stack moveStack;
    bool finishedMaze = false;
    bool resetStack = false;
    moveStack.push('s');
    moveStack.push('a');
    moveStack.push('d');
    moveStack.push('w');
    char currentMove;
    while (!finishedMaze)
    {
        if (_level->checkAllEnemiesDefeated() and !resetStack)
        { /// Once all enemies are defeated, the autoMover resets
            /// Empty the moveStack
            moveStack.setTop(nullptr);
            pushMoves(&moveStack, 'w');
            for (int i=0; i<size; i++) /// Set all the WKD spots to SPC
            {
                for (int j=0; j<size; j++)
                {
                    if (_level->maze[i][j] == WKD)
                    {
                        _level->maze[i][j] = SPC;
                    }
                }
            }
            resetStack = true;
        }
        currentMove = moveStack.pop();
        if (currentMove != 'B')
        { /// Checks that we're not backtracking
            if (Entities::nextInDirection((*_level), currentMove) != WKD)
            { /// Checks that we're not going somewhere we already went
                if (Entities::canMoveInDirection((*_level), currentMove))
                { /// Checks if we can move in the direction
                    finishedMaze = move(currentMove, _level, true);
                    system("cls");
                    _level->display();
                    pushMoves(&moveStack, currentMove); /// Pushes more moves to the stack
                    Sleep(50);
                }
            }
        }
        else
        { /// Checks that we are backtracking
            currentMove = moveStack.pop();
            if (Entities::canMoveInDirection((*_level), currentMove))
            { /// Doesn't push more moves to the stack
                finishedMaze = move(currentMove, _level, true);
                system("cls");
                _level->display();
                Sleep(50);
            }
        }
    }
    return;
}


void Player::removeFromItems(Item *_itemToRemove)
{
    if (_itemToRemove == nullptr)
    {
        return;
    }
    for (int i=0; i<10; i++)
    { /// Iterates through the items list
        if (items[i] != nullptr)
        {
            if (items[i] == _itemToRemove)
            {
                for (int j=i; j<9; j++)
                { /// Removes the item
                    items[j] = items[j+1];
                }
                items[9] = nullptr;
                i=10;
            }
        }
    }
}
Item** Player::getItems()
{
    return items;
}
