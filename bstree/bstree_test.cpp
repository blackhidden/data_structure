#include <iostream>
#include "bstree.h"

int main()
{
	Bstree<int> bstree;
	bstree.insert(5);
	bstree.insert(3);
	bstree.insert(7);
	bstree.insert(4);
	bstree.print(std::cout);
	bstree.erase(5);
	bstree.erase(10);
	bstree.print(std::cout);
	return 0;
}
