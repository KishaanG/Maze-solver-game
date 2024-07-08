#include "Item.h"
class Entities;
class Player;
#ifndef DAMAGING_H
#define DAMAGING_H


class Damaging : public Item
{
    public:
        Damaging(); // Default Constructor
        Damaging(int, int, char, string, int); // Custom Constructor
        virtual ~Damaging(); // Destructor
        void useItem(Player*, Entities*);
        void displayUsedItem(Player, Entities);

    private:
        int damageAmount;
};

#endif // DAMAGING_H
