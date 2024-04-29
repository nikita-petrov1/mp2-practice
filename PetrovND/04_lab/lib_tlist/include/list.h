#ifndef _LIST_H
#define _LIST_H
#include "node.h"
#include "monom.h"
#include <iostream>
using namespace std;

template <typename T>
class TList {
protected:
	TNode<T>* pFirst;
	TNode<T>* pCurr;
	TNode<T>* pStop;
	TNode<T>* pLast;
public:
	TList();
	TList(TNode<T>* _pFirst);
	TList(const TList<T>& list);
	virtual ~TList();
	TNode<T>* search(const T& data);
	void descendingInsert(const T& d);
	virtual void insertFirst(const T& data); 
	virtual void insertLast(const T& data);
	void insertAfter(const T& data, const T& afterdata);
	void insertBefore(const T& data, const T& beforedata);
	virtual void remove(const T& data);
	virtual void clear();
	int getSize() const;
	bool isEmpty() const;
	bool isFull() const;
	TNode<T>* getCurrent() const;
	void next();
	void reset();

	class Iterator {
	private:
		TNode<T>* pNode;
	public:
		Iterator(TNode<T>* node) : pNode(node) {}

		T& operator*() const {
			return pNode->data;
		}

		Iterator& operator++() {
			pNode = pNode->pNext;
			return *this;
		}
		Iterator operator++(int) {
			Iterator temp = *this;
			++(*this);
			return temp;
		}

		bool operator==(const Iterator& other) const {
			return pNode == other.pNode;
		}

		bool operator!=(const Iterator& other) const {
			return pNode != other.pNode;
		}
	};
	Iterator begin() const {
		return Iterator(pFirst);
	}

	Iterator end() const {
		if (isEmpty()) return pFirst;
		return Iterator(pStop);
	}
};

template<typename T>
TList<T>::TList() {
	pFirst = nullptr;
	pLast = nullptr;
	pCurr = nullptr;
	pStop = nullptr;
}

template <typename T>
TList<T>::TList(TNode<T>* _pFirst) {
	pFirst = _pFirst;
	pCurr = pFirst;
	pStop = nullptr;
	TNode<T>* tmp = pFirst;
	while (tmp->pNext != nullptr)
		tmp = tmp->pNext;
	pLast = tmp;
}

template <typename T>
TList<T>::TList(const TList<T>& l) {
	if (l.pFirst == nullptr) {
		pFirst = nullptr;
		pLast = nullptr;
		pCurr = nullptr;
		pStop = nullptr;
		return;
	}
	pFirst = new TNode<T>(l.pFirst->data);
	TNode<T>* tmp = pFirst;
	TNode<T>* ltmp = l.pFirst->pNext;
	while (ltmp != l.pStop){
		tmp->pNext = new TNode<T>(ltmp->data);
		tmp = tmp->pNext;
		ltmp = ltmp->pNext;
	}
	pLast = tmp;
	pCurr = pFirst;
	pStop = nullptr;
}

template<typename T>
void TList<T>::clear() {
	if (pFirst == nullptr) { return; }
	TNode<T>* curr = pFirst;
	TNode<T>* next = pFirst->pNext;
	while (next != pStop) {
		delete curr;
		curr = next;
		next = curr->pNext;
	}
	delete curr;
	pCurr = nullptr;
	pFirst = nullptr;
	pLast = nullptr;
}

template <typename T>
TList<T>::~TList() {
	clear();
}

template<typename T>
TNode<T>* TList<T>::search(const T& data_) {
	TNode<T>* tmp = pFirst;
	while (tmp != pStop && tmp->data != data_) {
		tmp = tmp->pNext;
	}
	if (tmp == pStop) { throw "ERROR: data not found!"; }
	return tmp;
}

template <typename T>
void TList<T>::insertFirst(const T& data) {
	TNode<T>* newFirst = new TNode<T>(data, pFirst);
	pFirst = newFirst;
	if (pLast == nullptr){ pLast = pFirst; }
	pCurr = pFirst;
}

template <typename T>
void TList<T>::insertLast(const T& data) {
	if (pFirst == nullptr) {
		insertFirst(data);
		return;
	}
	TNode<T>* new_last = new TNode<T>(data);
	pLast->pNext = new_last;
	pLast = new_last;
}


template <typename T>
void TList<T>::insertAfter(const T& data, const T& afterData) {
	TNode<T>* pWhere = search(afterData);
	if (pWhere == nullptr) { throw "ERROR: afterData not found!"; }
	if (pWhere == pLast) {
		insertLast(data);
		return;
	}
	TNode<T>* new_node = new TNode<T>(data, pWhere->pNext);
	pWhere->pNext = new_node;
}

template <typename T>
void TList<T>::insertBefore(const T& who, const T& where) {
	if (pFirst == nullptr) { throw "ERROR: list is empty!"; }
	TNode<T>* prev = nullptr;
	TNode<T>* curr = pFirst;
	while (curr != pStop && curr->data != where) {
		prev = curr;
		curr = curr->pNext;
	}
	if (curr == pStop) { throw "ERROR: beforeData not found!"; }
	if (prev == nullptr) {
		insertFirst(who);
		return;
	}
	TNode<T>* new_node = new TNode<T>(who, curr);
	prev->pNext = new_node;
}

template<typename T>
void TList<T>::remove(const T& data_) {
	if (pFirst == nullptr) { throw "ERROR: list is empty!"; }

	TNode<T>* prev = nullptr;
	TNode<T>* curr = pFirst;

	while (curr != pStop && curr->data != data_) {
		prev = curr;
		curr = curr->pNext;
	}

	if (curr == pStop) { throw "ERROR: data not found!"; }

	if (prev == nullptr) {
		pFirst = curr->pNext;
	}
	else {
		prev->pNext = curr->pNext;
	}

	if (curr == pLast) {
		pLast = prev;
	}

	delete curr;
}

template<typename T>
void TList<T>::descendingInsert(const T& d) {
	if (isEmpty()) { insertFirst(d); }
	else {
		while (pCurr != pStop) {
			if (pCurr->data <= d) {
				insertBefore(d, pCurr->data);
				break;
			} else if (pCurr->pNext == pStop) { insertLast(d); break; }
			next();
		}
	}
	reset();
}

template<typename T>
int TList<T>::getSize() const {
	if (pFirst == nullptr)  return 0;
	int size = 0;
	TNode<T>* tmp = pFirst;
	while (tmp != pStop) {
		size++;
		tmp = tmp->pNext;
	}
	return size;
}

template<typename T>
bool TList<T>::isEmpty()const {
	return (pFirst == nullptr);
}

template<typename T>
bool TList<T>::isFull()const {
	TNode<T>* tmp = new TNode<T>();
	if (tmp == nullptr) {
		return true;
	}
	return false;
}

template<typename T>
TNode<T>* TList<T>::getCurrent()const {
	return pCurr;
}

template<typename T>
void TList<T>::next() {
	if (pCurr == pStop) { throw "ERROR: list out of range!"; }
	pCurr = pCurr->pNext; 
}

template<typename T>
void TList<T>::reset() {
	pCurr = pFirst;
}

template<>
inline void TList<Monom>::descendingInsert(const Monom& m) {
	if (m.getCoeff() == 0) return;
	if (isEmpty()) { insertFirst(m); }
	else {
		while (pCurr != pStop) {
			if (pCurr->data < m) {
				insertBefore(m, pCurr->data);
				break;
			}
			else if (pCurr->data.getDegree() == m.getDegree()) {
				if (pCurr->data.getCoeff() + m.getCoeff() == 0) {
					remove(pCurr->data);
					break;
				}
				pCurr->data = (pCurr->data + m);
				break;
			}
			else if (pCurr->pNext == pStop) { insertLast(m); break; }
			next();
		}
	}
	reset();
}
#endif 