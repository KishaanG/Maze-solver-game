class Container;
#ifndef STACK_H
#define STACK_H

class Stack
{
	private:
		Container *top;

	public:
		Stack(); // Default Constructor
		Stack(Container*); // Custom Constructor
		virtual ~Stack(); // Destructor

		Container *getTop();
		void setTop(Container*);
		char pop();
		char peek();
		void push(char);
		void display();
};

#endif
