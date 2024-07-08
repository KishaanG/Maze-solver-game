#include <iostream>
#include "Item.h"
#include "Player.h"
#include "Entities.h"
using namespace std;

Item::Item()
{
    //ctor
    string name = "";
    isPickedUp = false;
    xPos = 0;
    yPos = 0;
}

Item::Item(int _xPos, int _yPos, char _img, string _name) : Object(_xPos, _yPos, _img, _name)
{
    //custom ctor
    isPickedUp = false;
}

Item::~Item()
{
    //dtor
}

void Item::setIsPickedUp(bool _isPickedUp)
{
    isPickedUp = _isPickedUp;
    return;
}

string Item::getName()
{
    return name;
}

bool Item::getIsPickedUp()
{
    return isPickedUp;
}

void Item::useItem(Player *_player, Entities *_opposingEntity)
{ /// Polymorphism function depending on healing or damaging Item
    if (_player != nullptr and _opposingEntity != nullptr)
    {
        _player->removeFromItems(this); /// Removes the Item from the player's Items list
    }
    return;
}

void Item::displayUsedItem(Player _player, Entities _entity)
{ /// Polymorphism function depending on healing or damaging Item
    cout << "The player used a " << name << "!" << endl; /// Displays the Item the player used
    return;
}

void Item::displayPickedUp()
{
    cout << "You picked up a " << name <<"!" << endl; /// Displays the name of the picked up Item
    return;
}
