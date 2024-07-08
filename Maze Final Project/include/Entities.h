#include "Level.h"
#include "Object.h"
#include <iostream>
using namespace std;
class Moves;
#ifndef ENTITIES_H
#define ENTITIES_H

class Entities : public Object
{
    public:
        Entities(); // Default Constructor
        Entities(string, string, int, int, char, int); // Custom Constructor
        virtual ~Entities(); // Destructor
        char nextInDirection(Level, char);
        bool canMoveInDirection(Level, char);
        string getType();
        void setType(string);
        int getHealth();
        void setHealth(int);
        int getInitialHealth();
        void setInitialHealth(int);
        void addMove(Moves*);
        int getNumOfMoves();
        Moves** getMoves();
        void displayHealth();

    protected:
        string type;
        int health;
        int initialHealth;
        Moves *moves[4];
};

#endif // ENTITIES_H
