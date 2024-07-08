#include "Entities.h"
#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Entities
{
    public:
        Enemy(); // Default Constructor
        Enemy(string, string, int, int, char, int); // Custom Constructor
        virtual ~Enemy(); // Destructor
        void autoMover(Level*);
        bool getIsAlive();
        void setIsAlive(bool);

    private:
        bool isAlive;
};

#endif // ENEMY_H
