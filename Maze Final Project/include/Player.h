#include "Entities.h"
#include "Level.h"
#include "Enemy.h"
class Item;
#ifndef PLAYER_H
#define PLAYER_H


class Player : public Entities
{
    public:
        Player(); // Default Constructor
        Player(string, string, int, int, int); // Custom Constructor
        virtual ~Player(); // Destructor
        bool move(char, Level*, bool);
        bool combat(Enemy*);
        void combatDisplay(Enemy);
        void autoMover(Level*);
        bool canMoveInDirection(Level, char);
        char nextInDirection(Level, char);
        void removeFromItems(Item*);
        Item** getItems();

    private:
        Item *items[10];
        int numOfItems;
};

#endif // PLAYER_H
