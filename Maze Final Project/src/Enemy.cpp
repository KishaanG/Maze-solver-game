#include <iostream>
#include "Enemy.h"
#include "Moves.h"
using namespace std;

Enemy::Enemy() : Entities()
{
    //ctor
}

Enemy::Enemy(string _name, string _type, int _xPos, int _yPos, char _img, int _health) : Entities(_name, _type, _xPos, _yPos, _img, _health)
{
    //custom ctor
}

Enemy::~Enemy()
{
    //dtor
}

bool Enemy::getIsAlive()
{
    return isAlive;
}

void Enemy::setIsAlive(bool _isAlive)
{
    isAlive = _isAlive;
    return;
}
