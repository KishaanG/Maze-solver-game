#include <iostream>
#include "Entities.h"
using namespace std;
#ifndef MOVES_H
#define MOVES_H


class Moves
{
    public:
        Moves(); // Default Constructor
        Moves(string, int, string, int); // Custom Constructor
        virtual ~Moves(); // Destructor
        string getName();
        int getDamage();
        int getUses();
        void setUses(int);
        int getInitialUses();
        string getType();
        void setType(string);
        double effectivenessAgainst(Entities);
        void performMove(Entities*);
        void displayMove(Entities, Entities);

    private:
        string name;
        int damage;
        string type;
        int uses;
        int initialUses;
};

#endif // MOVES_H
