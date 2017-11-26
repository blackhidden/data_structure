#ifndef _AVL_TREE_H_INCLUDED
#define _AVL_TREE_H_INCLUDED

#include "../bstree/bstree.h"

template<typename T>
class Avl_tree : public Bstree<T> {
public:
	typedef Bintree_node<T>* PBtn;

	void insert(const T& elem);
	void erase(const T& elem);

	PBtn single_rotate_with_left(PBtn pTn);
	PBtn single_rotate_with_right(PBtn pTn);
	PBtn double_rotate_with_left(PBtn pTn);
	PBtn double_rotate_with_right(PBtn pTn);
	using Bstree<T>::print;
private:
	PBtn insert(const T& elem, PBtn pTn);
	PBtn erase(const T& elem, PBtn pTn);
};

template<typename T>
inline typename Avl_tree<T>::PBtn Avl_tree<T>::single_rotate_with_left(PBtn pTn) {
	PBtn ptm = pTn->lchild;
	pTn->lchild = ptm->rchild;
	ptm->rchild = pTn;
	return ptm;
}

template<typename T>
inline typename Avl_tree<T>::PBtn Avl_tree<T>::single_rotate_with_right(PBtn pTn) {
	PBtn ptm = pTn->rchild;
	pTn->rchild = ptm->lchild;
	ptm->lchild = pTn;
	return ptm;
}

template<typename T>
inline typename Avl_tree<T>::PBtn Avl_tree<T>::double_rotate_with_left(PBtn pTn) {
	pTn->lchild = single_rotate_with_right(pTn->lchild);
	return single_rotate_with_left(pTn);
}

template<typename T>
inline typename Avl_tree<T>::PBtn Avl_tree<T>::double_rotate_with_right(PBtn pTn) {
	pTn->rchild = single_rotate_with_left(pTn->rchild);
	return single_rotate_with_right(pTn);
}

template<typename T>
inline void Avl_tree<T>::insert(const T& elem) {
	Bstree<T>::hb_root = insert(elem, Bstree<T>::hb_root);
}

template<typename T>
inline void Avl_tree<T>::erase(const T& elem) {
	Bstree<T>::hb_root = erase(elem, Bstree<T>::hb_root);
}

template<typename T>
inline typename Avl_tree<T>::PBtn Avl_tree<T>::insert(const T& elem, PBtn pTn) {
	if (pTn == 0) {
		pTn = new Bintree_node<T>(elem, 0, 0);
		++Bstree<T>::hb_size;
	} else {
		if (elem == pTn->element) {
			return pTn;
		}
		else if(elem < pTn->element) {
			pTn->lchild = insert(elem, pTn->lchild);
			if (Bstree<T>::depth(pTn->lchild) - Bstree<T>::depth(pTn->rchild) == 2) {
				if (elem < pTn->lchild->element)
					pTn = single_rotate_with_left(pTn);
				else
					pTn = double_rotate_with_left(pTn);
			}
		} else {
			pTn->rchild = insert(elem, pTn->rchild);
			if (Bstree<T>::depth(pTn->lchild) - Bstree<T>::depth(pTn->rchild) == 2) {
				if (elem > pTn->rchild->element)
					pTn = single_rotate_with_right(pTn);
				else
					pTn = double_rotate_with_right(pTn);
			}
		}
	}
	return pTn;
}

template<typename T>
inline typename Avl_tree<T>::PBtn Avl_tree<T>::erase(const T& elem, PBtn pTn) {
	if (pTn == 0)
		std::cerr << "error, the element not exist!\n";
	else {
		if (elem < pTn->element) {
			pTn->lchild = erase(elem, pTn->lchild);
			if (Bstree<T>::depth(pTn->rchild) - Bstree<T>::depth(pTn->lchild) == 2) {
				if (Bstree<T>::depth(pTn->rchild->rchild) > Bstree<T>::depth(pTn->rchild->lchild))
					pTn = single_rotate_with_right(pTn);
				else
					pTn = double_rotate_with_right(pTn);
			}
		}
		else if(elem > pTn->element) {
			pTn->rchild = erase(elem, pTn->rchild);
			if (Bstree<T>::depth(pTn->lchild) - Bstree<T>::depth(pTn->rchild) == 2) {
				if (Bstree<T>::depth(pTn->lchild->lchild) > Bstree<T>::depth(pTn->lchild->rchild))
					pTn = single_rotate_with_left(pTn);
				else
					pTn = double_rotate_with_right(pTn);
			}
		}
		else {
			if (pTn->lchild != 0 && pTn->rchild != 0) {
				PBtn ptm = Bstree<T>::delete_min(pTn->rchild);
				if (ptm == pTn->rchild)
					pTn->rchild = ptm->rchild;
				pTn->element = ptm->element;
				delete ptm;
				--Bstree<T>::hb_size;
			}
			else {
				PBtn ptm = pTn;
				if (pTn->lchild == 0)
					pTn = pTn->lchild;
				else
					pTn = pTn->rchild;
				delete ptm;
				--Bstree<T>::hb_size;	
			}
		}
	}
	return pTn;
}


#endif
