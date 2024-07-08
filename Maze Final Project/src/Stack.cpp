#include <iostream>
#include "Stack.h"
#include "Container.h"
using namespace std;

Stack::Stack()
{
	//ctor
	top = nullptr;
}

Stack::Stack(Container *_top)
{
	//custom ctor
	top = _top;
}

Stack::~Stack()
{
	//dtor
}

Container* Stack::getTop()
{
	return top;
}

void Stack::setTop(Container *_top)
{
	top = _top;
	return;
}

char Stack::pop()
{ /// Returns the top character from the stack and removes it from the stack
	if (top != nullptr)
	{
		Container *topContainer = top;
		top = top->getNext();
		topContainer->setNext(nullptr);
		char returnValue = topContainer->getContents();
		delete topContainer;
		return returnValue;
	}
	return 0;
}

char Stack::peek()
{ /// Returns the top character from the stack
	if(top != nullptr)
	{
		return top->getContents();
	}
	return 0;
}

void Stack::push(char _value)
{ /// Pushes a new character onto the stack
	Container * newContainer = new Container(_value, top);
	top = newContainer;
	return;
}

void Stack::display()
{ /// Displays the stack
	Container *iterator = top;
	while (iterator != nullptr)
	{ /// Displays the container pointers that aren't nullptr
		cout << (*iterator).getContents() << endl;
		iterator = (*iterator).getNext();
	}
	return;
}
