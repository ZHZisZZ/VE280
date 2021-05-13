//
// Created by cyx on 20-5-29.
//

#ifndef INTLIST_IMPL_H
#define INTLIST_IMPL_H

#include <iostream>
#include "mylist.h"

template <class T>
void List<T>::print()
{
    node_t<T>* itr = first;
    while(itr){
        std::cout << itr->val;
        itr = itr->next;
    }
    std::cout << "\n";
}

template <class T>
void List<T>::removeAll()
{
    while (!isEmpty()) removeFront();
}

template <class T>
void List<T>::copyFrom(const List &l)
{
    removeAll();
    auto desPt = first;
    for (auto srcPt = l.first; srcPt; srcPt = srcPt->next) {
        if (isEmpty()) {
            first = desPt = new node_t<T>;
        } else {
            desPt = desPt->next = new node_t<T>;
        }
        desPt->val = srcPt->val;
        desPt->next = nullptr;
    }
    last = desPt;
}

template <class T>
bool List<T>::isEmpty() const
{
    return !first;
}

template <class T>
void List<T>::insertBack(T val)
{
    if (!last) {
        first = last = new node_t<T>;
    }
    else {
        last = last->next = new node_t<T>;
    }
    last->val = val;
    last->next = nullptr;
}

template <class T>
T List<T>::removeFront()
{
    if (isEmpty()) throw emptyList();
    auto victim = first;
    first = first->next;
    if (isEmpty()) last = nullptr;
    auto tempV = victim->val;
    delete victim;
    return tempV;
}

template <class T>
const node_t<T>* List<T>::returnHead() const
{
    return first;
}

template <class T>
List<T>::List() : first(nullptr), last(nullptr)
{
}

template <class T>
List<T>::List(const List &l) : first(nullptr), last(nullptr)
{
    copyFrom(l);
}

template <class T>
List<T>& List<T>::operator=(const List &l)
{
    if (&l == this) return *this;
    copyFrom(l);
    return *this;
}

template <class T>
List<T>::~List() {
    removeAll();
}

bool isLarger(const List<int> &a, const List<int> &b)
{
    auto pa = a.returnHead();
    auto pb = b.returnHead();
    bool islarger = false;
    while (pa && pb) {
        if (pa->val > pb->val) islarger = true;
        else if (pa->val < pb->val) islarger = false;
        pa = pa->next;
        pb = pb->next;
    }
    if (pa || pb) {
        islarger = pa ? true : false;
    }
    return islarger;
}


List<int> Add(const List<int> &a, const List<int> &b)
{
    int ca = 0;
    List<int> l;
    auto pa = a.returnHead();
    auto pb = b.returnHead();
    while (pa || pb || ca) {
        int sum = (pa?pa->val:0) + (pb?pb->val:0) + ca;
        ca = sum / 10;
        sum %= 10;
        l.insertBack(sum);
        pa = pa?pa->next:nullptr;
        pb = pb?pb->next:nullptr;
    }
    return l;
}
#endif //INTLIST_IMPL_H
