/*
 * This is an exercise of VE280 Lab 10, SU2020.
 * Written by Martin Ma.
 * Latest Update: 7/17/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#ifndef MY_STACK_IMPL_H
#define MY_STACK_IMPL_H

#include <iostream>
#include <vector>
#include "my_stack.h"


template <class T>
void Stack<T>::print()
{
    Node<T>* itr = head;
    while(itr){
        std::cout << itr->val;
        itr = itr->next;
    }
    std::cout << "\n";
}

template <class T>
void Stack<T>::removeAll()
{
    while (!isEmpty()) pop();
}

template <class T>
void Stack<T>::copyFrom(const Stack &s)
{
    removeAll();
    copyFrom_helper(s.head);
}

template <class T>
void Stack<T>::copyFrom_helper(Node<T> *pt)
{
    if (!pt) return;
    copyFrom_helper(pt->next);
    push(pt->val);
}

template <class T>
Stack<T>::Stack() : head(nullptr)
{
}

template <class T>
Stack<T>::Stack(const Stack &s) : head(nullptr)
{
    copyFrom(s);
}

template <class T>
Stack<T> &Stack<T>::operator=(const Stack &s)
{
    if (&s == this) return *this;
    copyFrom(s);
    return *this;
}

template <class T>
Stack<T>::~Stack()
{
    removeAll();
}

template <class T>
bool Stack<T>::isEmpty() const
{
    return !head;
}

template <class T>
size_t Stack<T>::size() const
{
    int cnt = 0;
    auto itr = head;
    while(itr) { cnt++; itr = itr->next; }
    return cnt;
}

template <class T>
void Stack<T>::push(T val)
{
    head = new Node<T>(val, head); 
}

template <class T>
void Stack<T>::pop()
{
    if (isEmpty()) throw stackEmpty();
    auto victim = head;
    head = head->next;
    delete victim;
}

template <class T>
T Stack<T>::top() const
{
    if (isEmpty()) throw stackEmpty();
    return head->val;
}


template <class T>
void reverse(Stack<T> &s)
{
    std::vector<T> v;
    while (!s.isEmpty()) {
        v.push_back(s.top());
        s.pop();
    }
    for (const auto& e : v) {
        s.push(e);
    }
}

template <class T>
Stack<T> operator+(Stack<T> &s, T val)
{
    Stack<T> nstack(s);
    reverse(nstack);
    nstack.push(val);
    reverse(nstack);
    return nstack;
}

template <class T>
Stack<T> operator+(Stack<T> &first, Stack<T> &second)
{
     Stack<T> nstack1(first);
     Stack<T> nstack2(second);
     reverse(nstack1);
     while (!nstack2.isEmpty()) {
         nstack1.push(nstack2.top());
         nstack2.pop();
     }
     reverse(nstack1);
     return nstack1;
}

#endif //MY_STACK_IMPL_H