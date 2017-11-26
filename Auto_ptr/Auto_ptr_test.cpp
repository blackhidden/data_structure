#include <iostream>
#include "Auto_ptr.h"

int main()
{
	int *a = new int(5);
	Auto_ptr<int> p(a);
	std::cout<<*p<<"\n";
	return 0;
}
