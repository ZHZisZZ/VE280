#include "node.h"
#include <iostream>

void Node::addChild(Node *child)
{
    children[child_num++] = child;
}

Node::Node(int _value, int _n)
    : value(_value),     child_num(0),      
      n(_n), children(new Node *[_n])
{
}

Node::~Node()
{
    for (int i = 0; i < child_num; i++) {
        delete children[i];
    }
    delete [] children;
}

void Node::addChild(int _value)
{
    if (child_num == n) throw tooManyChildren();
    Node *child = new Node(_value, n);
    addChild(child);
}

void Node::traverse()
{
    std::cout << value << " ";
    for (int i = 0; i < child_num; i++) {
        children[i]->traverse();
    }
}

bool Node::contain_this(Node *sub)
{
    //if (!sub) return true;
    if (value != sub->value) return false;
    if (child_num != sub->child_num) return false;
    for (int i = 0; i < child_num; i++) {
        if (!children[i]->contain_this(sub->children[i])) return false;
    }
    return true;  
}

bool Node::contain(Node *sub)
{
    if (contain_this(sub)) return true;
    for (int i = 0; i < child_num; i++) {
        if (children[i]->contain(sub)) return true;
    }
    return false;
}

int Node::getHeight()
{
    if (!child_num) return 0;
    int maxH = 0;
    for (int i = 0; i < child_num; i++) {
        int curH = children[i]->getHeight();
        maxH = curH > maxH ? curH : maxH;
    }
    return maxH + 1;
}

Node& Node::operator[](int i)
{
    if (i >= child_num) throw invalidIndex();
    return *children[i];
}
