#include "Damaging.h"
#include "Player.h"
#include "Entities.h"
#include <iostream>
using namespace std;

Damaging::Damaging()
{
    //ctor
}

Damaging::Damaging(int _xPos, int _yPos, char _img, string _name, int _damageAmount) : Item(_xPos, _yPos, _img, _name)
{
    damageAmount = _damageAmount;
}

Damaging::~Damaging()
{
    //dtor
}

void Damaging::useItem(Player *_player, Entities *_opposingEntity)
{
    if (_player == nullptr or _opposingEntity == nullptr)
    {
        return;
    }
    _opposingEntity->setHealth(_opposingEntity->getHealth()-damageAmount); /// Applies the damage to the entities it damaged
    Item::useItem(_player, _opposingEntity); /// Removes the Item from the players' available Items
    return;
}

void Damaging::displayUsedItem(Player _player, Entities _entity)
{
    Item::displayUsedItem(_player, _entity); /// Displays the name of the Item used
    cout << "It did " << damageAmount << " damage." << endl; /// Displays the amount of damage done by the Item
    if (_entity.getHealth()-damageAmount<=0)
    { ///  Displays whether the opponent fainted from the Item's damage
        cout << _entity.getName() << " has fainted!" << endl;
    }
    return;
}
