#ifndef _THEADRINGLIST_H
#define _THEADRINGLIST_H
#include "list.h"
using namespace std;

template <typename T>
class THeadRingList : public TList<T> {
    TNode<T>* pHead;
public:  
    THeadRingList();
    THeadRingList(const THeadRingList& ringL);
    ~THeadRingList();

    void insertFirst(const T& data);
    void insertLast(const T& data);
    void remove(const T& data);
    void clear();
};

template <typename T>
THeadRingList<T>::THeadRingList() : TList<T>() {
    pHead = new TNode<T>();
    pStop = pHead;
}

template <typename T>
THeadRingList<T>::THeadRingList(const THeadRingList<T>& ringL) : TList<T>(ringL) {
    pHead = new TNode<T>(ringL.pHead->data, pFirst);
    if (!ringL.isEmpty())
        pLast->pNext = pHead;
    pStop = pHead;
}

template <typename T>
THeadRingList<T>::~THeadRingList() {
    delete pHead;
    pHead = nullptr;
}

template <typename T>
void THeadRingList<T>::insertFirst(const T& data) {
    TList<T>::insertFirst(data);
    pHead->pNext = pFirst;
    pStop = pHead;
    pLast->pNext = pHead;
}

template <typename T>
void THeadRingList<T>::insertLast(const T& data) {
    if (TList<T>::isEmpty()) {
        insertFirst(data);
        return;
    }
    TList<T>::insertLast(data);
    pLast->pNext = pHead;
}

template <typename T>
void THeadRingList<T>::remove(const T& data){
    if (pFirst == nullptr) { throw "ERROR: List is empty!"; }
    if (pFirst->data == data) {
        TNode<T>* curr = pFirst;
        if (curr->pNext == pHead) {
            delete curr;
            pFirst = nullptr;
            pCurr = nullptr;
            pLast = nullptr;
            pHead->pNext = nullptr;
            return;
        }
        pFirst = pFirst->pNext;
        pHead->pNext = pFirst;
        delete curr;
        return;
    }
    TList<T>::remove(data);
}

template <typename T>
void THeadRingList<T>::clear() {
    TList<T>::clear();
    delete pHead;
    pStop = pHead = nullptr;
}

#endif 