#include <iostream>
#include "avl_tree.h"

int main()
{
	Avl_tree<int> avl;
	avl.insert(5);
	avl.insert(4);
	avl.insert(8);
	avl.insert(11);
	avl.insert(12);
	avl.print_tree(std::cout);
	std::cout<<std::endl;
	avl.erase(4);
	avl.print_tree(std::cout);
	return 0;
}
