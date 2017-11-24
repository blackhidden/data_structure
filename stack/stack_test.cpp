#include <iostream>
#include "stack.h"

int main()
{
	Stack<int> stack;
	stack.push(2);
	stack.push(6);
	stack.push(9);
	int num=stack.size();
	for (int i=0; i!=num; ++i)
		std::cout<<stack.pop()<<"-";
	std::cout<<std::endl;
	return 0;
}
