#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const std::string &_str, int _num, Node *_left, Node *_right) 
    : str(_str), num(_num), left(_left), right(_right)
{
}

Node *Node::leftSubtree() const 
{
    return left;
}

void Node::setleft(Node *n)
{
    left = n;
}

Node *Node::rightSubtree() const 
{
    return right;
}

void Node::setright(Node *n)
{
    right = n;
}

string Node::getstr() const 
{
    return str;
}

int Node::getnum() const 
{
    return num;
}

void Node::incnum()
{
    num++;
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) 
{
    string nstring = leftNode->getstr() + rightNode->getstr();
    int nnum = leftNode->getnum() + rightNode->getnum();    
    return new Node(nstring, nnum, leftNode, rightNode);
}

/* =============================== Binary Tree =============================== */
BinaryTree::BinaryTree(Node *rootNode)
          : root(rootNode)
{
}


/* ----------------- delete ----------------- */ 
// EFFECTS: ~BinaryTree recursion helper function;
void delete_helper(Node *n)
{
    if (!n) return;
    delete_helper(n->leftSubtree());
    delete_helper(n->rightSubtree());
    delete n;
}
BinaryTree::~BinaryTree() 
{
    delete_helper(root);
}


/* ----------------- findPath ----------------- */ 
// 短，但是垃圾
// void findPath_helper(Node *n, const string &s, string current, string &result)
// {
//     if (n) {
//         if (n->getstr() == s) result = current;
//         else {
//             findPath_helper(n->leftSubtree(),  s, current+"0", result);
//             findPath_helper(n->rightSubtree(), s, current+"1", result);
//         } 
//     }
// }
// 长，但是布拉吉
// EFFECTS: findPath recursion helper function;
bool findPath_helper(Node *n, const string &s, string &result)
{
    if (!n) return false;
    if (n->getstr() == s) return true;
    result.push_back('0');
    if (findPath_helper(n->leftSubtree(),  s, result)) return true;
    result.pop_back();
    result.push_back('1');
    if (findPath_helper(n->rightSubtree(), s, result)) return true;
    result.pop_back();
    return false;
}
string BinaryTree::findPath(const string &s) const
{
    string result;
    return findPath_helper(root, s, result) ? result : "-1";
}


/* ----------------- sum ----------------- */ 
// EFFECTS: sum recursion helper function;
int sum_helper(Node *n)
{
    if (!n) return 0;
    return n->getnum() + sum_helper(n->leftSubtree()) + sum_helper(n->rightSubtree()); 
}
int BinaryTree::sum() const 
{
    return sum_helper(root);
}


/* ----------------- depth ----------------- */ 
// EFFECTS: depth recursion helper function;
int depth_helper(Node *n)
{
    if (!n) return 0;
    return max(depth_helper(n->leftSubtree()), depth_helper(n->rightSubtree())) + 1;
}
int BinaryTree::depth() const 
{
    return depth_helper(root);
}


/* ----------------- preorder_num ----------------- */ 
// EFFECTS: preorder_num recursion helper function;
void preorder_num_helper(Node *n)
{
    if (!n) return;
    cout << n->getnum() << " ";
    preorder_num_helper(n->leftSubtree());
    preorder_num_helper(n->rightSubtree());
}
void BinaryTree::preorder_num() const 
{
    preorder_num_helper(root);
    cout << endl;
}


/* ----------------- inorder_str ----------------- */ 
// EFFECTS: inorder_str recursion helper function;
void inorder_str_helper(Node *n)
{
    if (!n) return;
    inorder_str_helper(n->leftSubtree());
    cout << n->getstr() << " ";
    inorder_str_helper(n->rightSubtree());
}
void BinaryTree::inorder_str() const 
{
    inorder_str_helper(root);
    cout << endl;
}


/* ----------------- postorder_num ----------------- */ 
// EFFECTS: postorder_num recursion helper function;
void postorder_num_helper(Node *n)
{
    if (!n) return;
    postorder_num_helper(n->leftSubtree());
    postorder_num_helper(n->rightSubtree());
    cout << n->getnum() << " ";
}
void BinaryTree::postorder_num() const 
{
    postorder_num_helper(root);
    cout << endl;
}


/* ----------------- allPathSumGreater ----------------- */ 
// EFFECTS: allPathSumGreater recursion helper function;
bool allPathSumGreater_helper(Node *n, int sum)
{
    if (!n) return true;
    sum -= n->getnum();
    if (!n->leftSubtree() && !n->rightSubtree()) return sum < 0;
    return allPathSumGreater_helper(n->leftSubtree(),  sum) &&
           allPathSumGreater_helper(n->rightSubtree(), sum);
}
bool BinaryTree::allPathSumGreater(int sum) const 
{
    if (!root) return false;
    return allPathSumGreater_helper(root, sum);
}


/* ----------------- allPathSumGreater ----------------- */ 
// EFFECTS: covered_by recursion helper function;
// n1 contains n2
bool covered_by_helper(Node *n1, Node *n2)
{
    if (!n1 || !n2) return !n2;
    if (n1->getnum() != n2->getnum()) return false;
    return covered_by_helper(n1->leftSubtree(),  n2->leftSubtree()) &&
           covered_by_helper(n1->rightSubtree(), n2->rightSubtree());
} 
bool BinaryTree::covered_by(const BinaryTree &tree) const 
{
    //return covered_by_helper(root, tree.root);
    return covered_by_helper(tree.root, root);
}


/* ----------------- contained_by ----------------- */ 
// EFFECTS: contained_by recursion helper function;
bool contained_by_helper(Node *n1, Node *n2)
{
    if (!n1) return false;
    if (covered_by_helper(n1, n2)) return true;
    return contained_by_helper(n1->leftSubtree(),  n2) ||
           contained_by_helper(n1->rightSubtree(), n2); 
}
bool BinaryTree::contained_by(const BinaryTree &tree) const 
{
    // if (!tree.root) return true;
    // return contained_by_helper(root, tree.root);   
    if (!root) return true;
    return contained_by_helper(tree.root, root);
}


/* ----------------- copy ----------------- */ 
// EFFECTS: copy recursion helper function;
// void copy_helper(Node *n1, Node *n2)
// {
//     if (n2->leftSubtree()) {
//         n1->setleft(new Node(n2->leftSubtree()->getstr(), n2->leftSubtree()->getnum()));
//         copy_helper(n1->leftSubtree(), n2->leftSubtree());
//     }
//     if (n2->rightSubtree()) {
//         n1->setright(new Node(n2->rightSubtree()->getstr(), n2->rightSubtree()->getnum()));
//         copy_helper(n1->rightSubtree(), n2->rightSubtree());
//     }
// }
// BinaryTree BinaryTree::copy() const 
// {
//     Node* nroot = nullptr;
//     if (root) {
//         nroot = new Node(root->getstr(), root->getnum());
//         copy_helper(nroot, root);
//     }
//     return BinaryTree(nroot);
// }
Node *copy_helper(Node *root) {
    Node *n = nullptr;
    if (root) {
        n = new Node(root->getstr(), root->getnum(),
                     copy_helper(root->leftSubtree()), 
                     copy_helper(root->rightSubtree()));
    }
    return n;
}
BinaryTree BinaryTree::copy() const
{
    return BinaryTree(copy_helper(root));
}
