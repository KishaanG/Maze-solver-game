#include <iostream>
#include "Moves.h"
#include "Entities.h"


#include <windows.h>


using namespace std;

Moves::Moves()
{
    //ctor
    name = "";
    damage = 0;
    type = "";
    uses = 0;
    initialUses = 0;
}

Moves::Moves(string _name, int _damage, string _type, int _uses)
{
    //custom ctor
    name = _name;
    damage = _damage;
    type = _type;
    uses = _uses;
    initialUses = _uses;
}

Moves::~Moves()
{
    //dtor
}

string Moves::getName()
{
    return name;
}

int Moves::getDamage()
{
    return damage;
}

int Moves::getUses()
{
    return uses;
}

void Moves::setUses(int _uses)
{
    uses = _uses;
    return;
}

int Moves::getInitialUses()
{
    return initialUses;
}

string Moves::getType()
{
    return type;
}

void Moves::setType(string _type)
{
    type = _type;
    return;
}

double Moves::effectivenessAgainst(Entities _entity)
{ /// Returns the multiplier of the damage of a move
    string entityType = _entity.getType();
    if (type == "Fire")
    {
        if (entityType == "Water")
        { /// Returns 0.75 for not effective moves
            return 0.75;
        }
        else if (entityType == "Ground")
        { /// Returns 1.5 for very effective moves
            return 1.5;
        }
    }
    else if (type == "Water")
    {
        if (entityType == "Ground")
        {
            return 0.75;
        }
        else if (entityType == "Fire")
        {
            return 1.5;
        }
    }
    else if (type == "Ground")
    {
        if (entityType == "Fire")
        {
            return 0.75;
        }
        else if (entityType == "Water")
        {
            return 1.5;
        }
    }
    return 1.0; /// Returns 1 for neutral effective moves
}

void Moves::performMove(Entities *_attackedEntity)
{
    if (_attackedEntity == nullptr)
    {
        return;
    }
    double damageMultiplier = effectivenessAgainst((*_attackedEntity)); /// Gets the damage multiplier
    double totalDamage = damage*damageMultiplier; /// Determines the total damage
    _attackedEntity->setHealth(_attackedEntity->getHealth()-(int)totalDamage); /// Adjusts the health of the attacked entity
    uses--; /// Reduces the uses count by one
    return;
}

void Moves::displayMove(Entities _user, Entities _receiver)
{
    cout << _user.getName() << " uses " << name << "! "; /// Displays the name of the used move
    double effectiveness = effectivenessAgainst(_receiver);
    if (effectiveness == 1.5)
    { /// Displays whether or not the move was effective
        cout << "It is super effective.";
    }
    else if (effectiveness == 0.75)
    {
        cout << "It is not very effective.";
    }
    cout << endl;
    if (_receiver.getHealth()<=0)
    { /// Displays whether or not the attacked entity lost all it's health
        cout << _receiver.getName() << " has fainted!" << endl;
    }
    return;
}
