#include <iostream>
#include "Object.h"
class Player;
class Entities;
using namespace std;
#ifndef ITEM_H
#define ITEM_H

class Item : public Object
{
    public:
        Item(); // Default Constructor
        Item(int, int, char, string); // Custom Constructor
        virtual ~Item(); // Destructor
        void setIsPickedUp(bool);
        string getName();
        bool getIsPickedUp();
        virtual void useItem(Player*, Entities*);
        virtual void displayUsedItem(Player, Entities);
        void displayPickedUp();

    protected:
        bool isPickedUp;


    private:
};

#endif // ITEM_H
