#include <iostream>
#include "sorting.h"

int main() {
	int a[] = {3, 34, 2, 5, 30, 1, 11, 22, 4, 8};
//	bubble_sort(a, 10);
//	select_sort(a, 10);
//	insertion_sort(a, 10);
//	shell_sort(a, 10);
//	heap_sort(a, 10);
//	merge_sort_rec(a, 10);
//	quick_sort(a, 10);
	count_sort(a, 10);
	for (int i=0; i!=10; ++i)
		std::cout<<a[i]<<" ";
	std::cout<<'\n';
	return 0;
}
