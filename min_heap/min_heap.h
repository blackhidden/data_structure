#ifndef _MIN_HEAP_H_INCLUDED
#define _MIN_HEAP_H_INCLUDED

#include "../heap/heap.h"
#include <iostream>

template<typename T>
class Min_heap : public Heap<T> {
public:
	explicit Min_heap(int max_size, const T lower_limit);
	~Min_heap();
	virtual void insert(const T& elem);
	T erase_min();
	T find_min();

	virtual void decrease_key(int p, T val);
	virtual void increase_key(int p, T val);

	using Heap<T>::Heap;
	using Heap<T>::full;
	using Heap<T>::hb_size;
	using Heap<T>::hb_elememt;
	using Heap<T>::empty;
};

template<typename T>
inline Min_heap<T>::Min_heap(int max_size, const T lower_limit){
	Heap<T>::hb_size = max_size;
	Heap<T>::hb_element[0] = lower_limit;
}

template<typename T>
inline Min_heap<T>::~Min_heap() {}

template<typename T>
inline void Min_heap<T>::insert(const T& elem) {
	if (full()) {
		std::cerr << "error, the heap is full!\n";
		return;
	}
	int i = ++hb_size;
	for (; Heap<T>::hb_element[i >> 1] > elem; i = i >> 1)
		Heap<T>::hb_element[i] = Heap<T>::hb_element[i >> 1];
	Heap<T>::b_element[i] = elem;
}

template<typename T>
T Min_heap<T>::erase_min() {
	if (empty()) {
		std::cerr << "error, the heap is empty!\n";
		return Heap<T>::hb_element[0];
	}

	T min_element = Heap<T>::hb_element[1];
	T last_element = Heap<T>::hb_element[hb_size--];
	int i, child;
	for (int i = 0; (i << 1) <= hb_size; i = child) {
		child = i << 1;
		if (child != Heap<T>::hb_size && Heap<T>::hb_element[child] > Heap<T>::hb_element[child+1])
			child++;
		if (last_element <= Heap<T>::hb_element[child])
			break;
		Heap<T>::hb_element[i] = Heap<T>::hb_element[child];
	}
	Heap<T>::hb_element[i] = last_element;
	return min_element;
}

template<typename T>
inline T Min_heap<T>::find_min() {
	if (empty()) {
		std::cerr << "the heap is empty!\n";
		return Heap<T>::hb_element[0];
	}
	return Heap<T>::hb_element[1];
}

template<typename T>
inline void Min_heap<T>::decrease_key(int p, T val) {
	if (p > hb_size) {
		std::cerr << "error, the element not exist!\n";
		return;
	}
	int elem = Heap<T>::hb_element[p] - val;
	if (elem <= Heap<T>::hb_element[0]) {
		std::cerr << "error, the key decrease too much!\n";
		return;
	}
	Heap<T>::hb_element[p] = elem;
	int i = p;
	for (; i != 0; i = i >> 1) {
		if (elem < Heap<T>::hb_element[i>>1])
			Heap<T>::hb_element[i] = Heap<T>::hb_element[i>>1];
		else break;
	}
	Heap<T>::hb_element[i] = elem;
}

template<typename T>
inline void Min_heap<T>::increase_key(int p, T val) {
	if (p > hb_size) {
		std::cerr << "error, the element not exist!\n";
		return;
	}
	Heap<T>::hb_element[p] += val;
	int elem = Heap<T>::hb_element[p];
	int i = p;
	int child;
	for (; i != hb_size; i = child) {
		child = i << 1;
		if (child != hb_size && Heap<T>::hb_element[child] > Heap<T>::hb_element[child+1])
			child++;
		if (elem > Heap<T>::hb_elememt[child])
			Heap<T>::hb_element[i] = Heap<T>::hb_element[child];
		else
			break;
	}
	Heap<T>::hb_element[i] = elem;
}

#endif
