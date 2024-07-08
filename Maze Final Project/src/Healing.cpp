#include "Healing.h"
#include "Player.h"
#include "Entities.h"
#include <iostream>
using namespace std;

Healing::Healing()
{
    //ctor
}

Healing::Healing(int _xPos, int _yPos, char _img, string _name, int _healAmount) : Item(_xPos, _yPos, _img, _name)
{
    //custom ctor
    healAmount = _healAmount;
}

Healing::~Healing()
{
    //dtor
}

void Healing::useItem(Player *_player, Entities *_opposingEntity)
{
    if (_player != nullptr and _opposingEntity != nullptr)
    {
        if (_player->getHealth()+healAmount >= _player->getInitialHealth())
        { /// Heals the player to full health rather than higher than the max health
            _player->setHealth(_player->getInitialHealth());
        }
        else
        { /// Heals the player the healAmount
            _player->setHealth(_player->getHealth()+healAmount);
        }
        Item::useItem(_player, _opposingEntity);
    }
    return;
}

void Healing::displayUsedItem(Player _player, Entities _entity)
{
    Item::displayUsedItem(_player, _entity); /// Displays the Item's name
    cout << "It healed " << healAmount << "." << endl; /// Displays the healAmount of the Item
    return;
}
