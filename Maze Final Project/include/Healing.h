#include "Item.h"
class Entities;
class Player;
#ifndef HEALING_H
#define HEALING_H


class Healing : public Item
{
    public:
        Healing(); // Default Constructor
        Healing(int, int, char, string, int); // Custom Constructor
        virtual ~Healing(); // Destructor
        void useItem(Player*, Entities*);
        void displayUsedItem(Player, Entities);

    private:
        int healAmount;
};

#endif // HEALING_H
