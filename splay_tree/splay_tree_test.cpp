#include <iostream>
#include "splay_tree.h"

int main()
{
	Splay_tree<int> sptree;
	sptree.insert(12);
	sptree.insert(5);
	sptree.insert(25);
	std::cout<<"insert 12, 5, 25:\n";
	sptree.print_tree(std::cout);
	sptree.erase(5);
	std::cout<<"erase 5:\n";
	sptree.print_tree(std::cout);
	std::cout<<"the minimal element: ";
	std::cout<<sptree.find_min()->element<<"\n";
	std::cout<<"the maximal element: ";
	std::cout<<sptree.find_max()->element<<"\n";
	return 0;
}
