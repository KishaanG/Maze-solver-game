#include "Object.h"

Object::Object()
{
    //ctor
}

Object::~Object()
{
    //dtor
}

Object::Object(int _xPos, int _yPos, char _img, string _name)
{
    //custom ctor
    xPos = _xPos;
    yPos = _yPos;
    img = _img;
    name = _name;
}
int Object::getXPos()
{
    return xPos;
}

int Object::getYPos()
{
    return yPos;
}

void Object::setXPos(int _xPos)
{
    xPos = _xPos;
    return;
}

void Object::setYPos(int _yPos)
{
    yPos = _yPos;
    return;
}

void Object::setName(string _name)
{
    name = _name;
    return;
}

string Object::getName()
{
    return name;
}
char Object::getImg()
{
    return img;
}
