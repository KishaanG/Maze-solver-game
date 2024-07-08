#include <iostream>
using namespace std;
#ifndef OBJECT_H
#define OBJECT_H

class Object
{
    public:
        Object(); // Default Constructor
        Object(int, int, char, string); // Custom Constructor
        virtual ~Object(); // Destructor
        int getXPos();
        int getYPos();
        void setXPos(int);
        void setYPos(int);
        char getImg();
        void setName(string);
        string getName();

    protected:
        int xPos;
        int yPos;
        char img;
        string name;
};

#endif // OBJECT_H
