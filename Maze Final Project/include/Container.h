#ifndef CONTAINER_H
#define CONTAINER_H

class Container
{
	public:
		Container(); // Default Constructor
		Container(char, Container*); // Custom Constructor
		virtual ~Container(); // Destructor

		Container* getNext();
		char getContents();

		void setNext(Container*);
		void setContents(char);

	private:
		Container *next;
		char contents;
};

#endif
