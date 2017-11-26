#ifndef _BSTREE_H_INCLUDED
#define _BSTREE_H_INCLUDED

#include <iostream>
#include "../binary_tree/binary_tree.h"

template<typename T>
class Bstree : public Binary_tree<T> {
public:
	typedef Bintree_node<T>* PBtn;
	PBtn find_min(PBtn pTn=0) const;
	PBtn find_max(PBtn pTn=0) const;

	PBtn find(const T& elem) const;
	virtual void insert(const T& elem);
	virtual void erase(const T& elem);
	virtual void print(std::ostream& output) const;

protected:
	PBtn hb_root;
	int hb_size;
	PBtn delete_min(PBtn pTn);
	virtual void print(std::ostream& output, const PBtn pTn) const;
};

template<typename T>
inline typename Bstree<T>::PBtn Bstree<T>::find_min(PBtn pTn) const {
	if (pTn == 0)
		return 0;
	if (pTn->lchild == 0)
		pTn = hb_root;
	while (pTn->lchild != 0)
		pTn = pTn->lchild;
	return pTn;
}

template<typename T>
inline typename Bstree<T>::PBtn Bstree<T>::find_max(PBtn pTn) const {
	if (pTn == 0)
		return 0;
	if (pTn->rchild == 0)
		return hb_root;
	while (pTn->rchild != 0)
		pTn = pTn->rchild;
	return pTn;
}

template<typename T>
inline typename Bstree<T>::PBtn Bstree<T>::find(const T& elem) const {
	PBtn pTn = hb_root;
	while (pTn != 0) {
		if (elem == pTn->element)
			return pTn;
		if (elem < pTn->element)
			pTn = pTn->lchild;
		else 
			pTn = pTn->rchild;
	}
	return 0;
}

template<typename T>
inline void Bstree<T>::insert(const T& elem) {
	if (hb_root == 0) {
		hb_root = new Bintree_node<T>(elem, 0, 0);
		++hb_size;
		return;
	}

	PBtn pTn = hb_root;
	while (true) {
		if (elem == pTn->element)
			return;
		if (elem < pTn->element) {
			if (pTn->lchild == 0) {
				pTn->lchild = new Bintree_node<T>(elem, 0, 0);
				++hb_size;
				return;
			}
			pTn = pTn->lchild;
		}
		else {
			if (pTn->rchild == 0) {
				pTn->rchild = new Bintree_node<T>(elem, 0, 0);
				++hb_size;
				return;
			}
			pTn = pTn->rchild;
		}
	}
}

template<typename T>
inline typename Bstree<T>::PBtn Bstree<T>::delete_min(PBtn pTn) {
	assert(pTn != 0);
	PBtn parent = pTn;
	while (pTn->lchild != 0) {
		parent = pTn;
		pTn = pTn->lchild;
	}
	if (parent != pTn)
		parent->lchild = pTn->rchild;
	return pTn;
}

template<typename T>
inline void Bstree<T>::erase(const T& elem) {
	PBtn pTn = hb_root;
	PBtn parent = pTn;
	while (pTn != 0) {
		if (elem == pTn->element) {
			if (pTn->lchild != 0 && pTn->rchild != 0) {//two children
				PBtn ptm = delete_min(pTn->rchild);
				//if the right child of pTn don't has left subtree
				if (ptm == pTn->rchild)
					pTn->rchild = ptm->rchild;
				pTn->element = ptm->element;
				delete ptm;
				--hb_size;
			} else {//one child or zero
				PBtn pReplace = pTn->lchild != 0 ? pTn->lchild : pTn->rchild;
				if (parent == pTn) {//delete the root node
					hb_root = pReplace;
				} else {
					if (parent->lchild == pTn)
						parent->lchild = pReplace;
					else 
						parent->rchild = pReplace;
				}
				delete pTn;
				--hb_size;
			}
			break;
		}
		parent = pTn;
		if (elem < pTn->element)
			pTn = pTn->lchild;
		else 
			pTn = pTn->rchild;
	}
	if (pTn == 0) {
		std::cerr << "error, the delete element not exit!\n";
	}
}




template<typename T>
inline void Bstree<T>::print(std::ostream& output) const {
	print(output, hb_root);
	output << std::endl;
}

template<typename T>
inline void Bstree<T>::print(std::ostream& output, const PBtn pTn) const {
	if (pTn == 0) return;
	print(output, pTn->lchild);
	output << pTn->element << ' ';
	print(output, pTn->rchild);
}

#endif
