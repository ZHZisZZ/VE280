#ifndef __DLIST_IMPL_H__
#define __DLIST_IMPL_H__

#include "dlist.h"

template<class T>
bool Dlist<T>::isEmpty() const
{
    return !first;
}

template<class T>
void Dlist<T>::insertFront(T *op)
{
    auto nPt = new node{first, nullptr, op};
    if (isEmpty()) {
        first = last = nPt;
    } else {
        first = first->prev = nPt;
    }
}

template<class T>
void Dlist<T>::insertBack(T *op)
{
    auto nPt = new node{nullptr, last, op};
    if (isEmpty()) {
        first = last = nPt;
    } else {
        last = last->next = nPt;
    }
}

template<class T>
T *Dlist<T>::removeFront()
{
    if (isEmpty()) throw emptyList();
    auto victim = first;
    T *vicValue = victim->op;
    first = first->next;
    if (isEmpty()) last = nullptr;
    else {
        first->prev = nullptr;
    }
    delete victim;
    return vicValue;
}

template <class T>
T *Dlist<T>::removeBack()
{
    if (isEmpty()) throw emptyList();
    auto victim = last;
    last = last->prev;
    if (!last) first = nullptr;
    else {
        last->next = nullptr;
    }
    T *vicValue = victim->op;
    delete victim;
    return vicValue;
}

template <class T>
T *Dlist<T>::remove(bool (*cmp)(const T*, const T*), T* ref)
{
    // return NULL pointer if no such node exists
    auto itr = first;
    for (; itr && !cmp(itr->op, ref); itr = itr->next) continue;
    if (!itr) return nullptr;
    // itr is victim;
    if (itr->prev) itr->prev->next = itr->next;
    else first = itr->next;
    if (itr->next) itr->next->prev = itr->prev;
    else last = itr->prev;
    T *vicValue = itr->op;
    delete itr;
    return vicValue;
}

template <class T>
void Dlist<T>::removeAll()
{
    while (!isEmpty()) delete removeFront();
}

template <class T>
void Dlist<T>::copyAll(const Dlist &l)
{
    removeAll();
    auto desPt = first;
    for (auto srcPt = l.first; srcPt; srcPt = srcPt->next) {
        if (isEmpty()) {
            first = desPt = new node{nullptr, nullptr, nullptr};
        } else {
            desPt = desPt->next = new node{nullptr, desPt, nullptr};
        }
        desPt->op = new T(*(srcPt->op));
    }
    last = desPt;
}

template <class T>
Dlist<T>::Dlist()
        : first(nullptr), last(nullptr)
{

}

template <class T>
Dlist<T>::Dlist(const Dlist &l)
        : first(nullptr), last(nullptr)
{
    copyAll(l);
}

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l)
{
    if (&l == this) return *this;
    copyAll(l);
    return *this;
}

template <class T>
Dlist<T>::~Dlist()
{
    removeAll();
}


#endif