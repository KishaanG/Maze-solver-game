#include <iostream>
#include "Container.h"
using namespace std;

Container::Container()
{
	//ctor
	next = nullptr;
	contents = 0;
}

Container::Container(char _contents, Container *_next)
{
	//custom ctor
	next = _next;
	contents = _contents;
}

Container::~Container()
{
	//dtor
}

Container* Container::getNext()
{
	return next;
}

char Container::getContents()
{
	return contents;
}

void Container::setNext(Container *_next)
{
	next = _next;
	return;
}

void Container::setContents(char _contents)
{
	contents = _contents;
	return;
}
