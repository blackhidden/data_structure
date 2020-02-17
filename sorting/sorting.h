#pragma once

//---------------bubble sort----------------------
template<typename T>
void bubble_sort(T a[], int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = n-1; j > i; --j) {
			if (a[j] < a[j-1]) {
				T tmp = a[j];
				a[j] = a[j-1];
				a[j-1] = tmp;
			}
		}
	}
}

//---------------select sort---------------------
template<typename T>
void select_sort(T a[], int n) {
	int minIndex = 0;
	for (int i = 0; i < n-1; ++i) {
		minIndex = i;
		for (int j = i+1; j < n; ++j) {
			if (a[j] < a[minIndex])
				minIndex = j;
		}
		if (minIndex != i) {
			T tmp = a[minIndex];
			a[minIndex] = a[i];
			a[i] = tmp;
		}
	}
}

//---------------insertion sort-------------------
template<typename T>
void insertion_sort(T a[], int n) {
	T tm;
	for (int i = 0; i != n; ++i) {
		tm = a[i];
		int k = i;
		for (; k > 0 && a[k-1] > tm; --k) {
			a[k] = a[k-1];
		}
		a[k] = tm;
	}
}

//---------------shell sort-------------------------
template<typename T>
void shell_sort(T a[], int n) {
	for (int increment = n/2; increment >= 1; increment /= 2) {
		if (increment %2 == 0) increment++;
		for (int i = increment; i < n; ++i) {
			T tm = a[i];
			int j = i;
			for (; j >= increment; j -= increment) {
				if (tm >= a[j-increment]) break;
				a[j] = a[j-increment];
			}
			a[j] = tm;
		}
	}
}

//-------------------------heap sort-----------------------------
template<typename T>
void percDown(T a[], int n, int i) {
	T tm = a[i];
	int child = i<<1;//leftchild(i) = 2 * i + 1
	for (; child < n-1; i = child, child = (child<<1)) {
		if (child != n-1 && a[child] > a[child+1])
			child++;
		if (tm > a[child])
			a[i] = a[child];
		else break;
	}
	a[i] = tm;
}

template<typename T>
void reverse(T a[], int n) {
	for (int i = 0; i != n/2; ++i) {
		T tm = a[i];
		a[i] = a[n-1-i];
		a[n-1-i] = tm;
	}
}

template<typename T>
void heap_sort(T a[], int n) {
	for (int i = n/2; i >= 0; --i)
		percDown(a, n, i);//build heap
	for (int j = n-1; j >= 0; --j) {
		T min = a[0];//delete min
		a[0] = a[j];
		a[j] = min;
		percDown(a, j, 0);
	}
	reverse(a, n);//order from big to small
}

//-------------------------merge sort recursive-----------------------------
template<typename T>
void merge_array(T a[], int beg, int end) {
	int center = (beg + end) / 2;
	for (int i = beg, j = center+1; i <= end && j <= end;) {
		if (a[i] > a[j]) {
			T tm = a[j];
			for (int k = j; k != i; --k)
				a[k] = a[k-1];
			a[i] = tm;
			++j;++i;
		}
		else ++i;
	}
}

template<typename T>
void m_sort(T a[], int left, int right) {
	if (left < right) {
		int center = (left + right) / 2;
		m_sort(a, left, center);
		m_sort(a, center+1, right);
		merge_array(a, left, right);
	}
}

template<typename T>
void merge_sort_rec(T a[], int n) {
	m_sort(a, 0, n-1);
}

//-------------------------merge sort non-recursive-------------------------
/*
template<typename T>
void merge_sort_nonrec(T a[], int n) {
	int i, left_min, left_max, right_min, right_max, next;
	int *tmp = (int*)malloc(sizeof(int) * n);
	for (int i = 1; i < n; i *= 2) {
		for (left_min = 0; left_min < n-i; left_min = right_max) {
			right_min = left_max = left_min + i;
			right_max = left_max + i;

			if (right_max > n)
				right_max = n;
			next = 0;
			while (left_min < left_max && right_min < right_max)
				tmp[next++] = a[left_min] > a[right_min] ? a[right_min++] : a[left_min++];
			while (left_min < left_max)
				a[--right_min] == a[--left_max];
			while (next > 0)
				a[--right_min] = tmp[--next];
		}
	}
	free(tmp);
}
*/
//---------------------------quick sort--------------------------------
template<typename T>
T median(T a[], int left, int right) {//median of three partitioning
	int center = (left + right) / 2;
	T tm;
	if (a[left] > a[center]) {
		tm = a[left];
		a[left] = a[center];
		a[center] = tm;
	}
	if (a[left] > a[right]) {
		tm = a[left];
		a[left] = a[right];
		a[right] = tm;
	}
	if (a[center] > a[right]) {
		tm = a[center];
		a[center] = a[right];
		a[right] = tm;
	}

	tm = a[center];
	a[center] = a[right-1];
	a[right-1] = tm;

	return a[right-1];
}

template<typename T>
void q_sort(T a[], int left, int right) {
	if (left + 4 < right) {
		T pivot = median(a, left, right);
		int i = left;
		int j = right - 1;
		while (true) {
			while (a[++i] < a[pivot]);
			while (a[--j] > a[pivot]);
			if (i < j) {
				T tm = a[i];
				a[i] = a[j];
				a[j] = tm;
			}
			else break;
		}
		T tm = a[i];
		a[i] = a[right-1];
		a[right-1] = tm;

		q_sort(a, left, i-1);
		q_sort(a, i+1, right);
	}
	else //if the array size is little than 5, use insertion sort
		insertion_sort(a+left, right-left+1);
}

template<typename T>
void quick_sort(T a[], int n) {
	q_sort(a, 0, n-1);
}

//--------------------------count sort------------------------------
#include<stdlib.h>
#include<cstring>
template<typename T>
void count_sort(T a[], int n) {
	T nMin, nMax;
	nMin = nMax = a[0];
	for (int i = 1; i < n; ++i) {
		if (a[i] > nMax)
			nMax = a[i];
		if (a[i] < nMin)
			nMin = a[i];
	}

	T *pCount = (T*)malloc(sizeof(T) * (nMax-nMin+1));
	memset(pCount, 0, sizeof(T) * (nMax-nMin+1));

	for (int i = 0; i < n; ++i)
		pCount[a[i]-nMin]++;

	int j = 0;
	for (int i = 0; i < nMax-nMin+1; ++i) {
		while (pCount[i] != 0) {
			a[j++] = i + nMin;
			pCount[i]--;
		}
	}
}

//------------------------bucket sort-----------------------------

//------------------------radix sort------------------------------

