#include "binaryTree.h"
#include "huffmanTree.h"
#include "iostream"
#include "fstream"
#include <algorithm>
#include <vector>
#include <string>

enum INPUT {SPACE, ENTER};

// EFFECTS: compare nodes
static bool cmp_node(Node *n1, Node *n2) 
{
    return n1->getnum() > n2->getnum() || (n1->getnum() == n2->getnum() && n1->getstr() > n2->getstr());
}

// EFFECTS: char -> index
static int char2index(char c) 
{
    if (c == ' ') return SPACE;
    if (c == '\n') return ENTER;
    return c - 95;
}

// EFFECTS: index -> char
static std::string index2str(int index) 
{
    if (index == SPACE) return " ";
    if (index == ENTER) return "\n";
    return std::string(1, char('a' - 2 + index));
}

// EFFECTS: construct Huffmantree from freqMap and return tree root
Node *getRoot(std::vector<int>& freqMap)
{
    // create nodes for the charatcer that appeared
    std::vector<Node*> nodeArray;
    for (int i = 0; i < freqMap.size(); i++) {
        if (!freqMap[i]) continue;
        nodeArray.push_back(new Node(index2str(i), freqMap[i]));
    }

    // construct tree
    while (nodeArray.size() != 1) {
        std::sort(nodeArray.begin(), nodeArray.end(), cmp_node);
        Node *noder = nodeArray.back(); nodeArray.pop_back();
        Node *nodel = nodeArray.back(); nodeArray.pop_back();
        Node *nodep = Node::mergeNodes(nodel, noder);
        nodeArray.push_back(nodep);
    }

    // return treeroot
    return nodeArray.back();
}

int main(int argc, char *argv[]) 
{   
    bool outputTree = false;
    std::ifstream fin;
    if (argv[1][0] == '-') {
        outputTree = true;
        fin.open(argv[2]);
    } else {
        fin.open(argv[1]);
    }

    // record the frequency of every character
    std::vector<int> freqMap(28, 0);
    char c;
    while (fin.get(c)) {
        if (c == '\r') continue;
        freqMap[char2index(c)]++;
    }
    fin.close();

    HuffmanTree tree(getRoot(freqMap));
    
    // construct lookup table of path;
    std::vector<std::string> lkupTable(28, "");
    for (int i = 0; i < freqMap.size(); i++) {
        if (!freqMap[i]) continue;
        lkupTable[i] = tree.findPath(index2str(i));
    }

    if (outputTree) tree.printTree();
    else {
        fin.open(argv[1]);
        while (fin.get(c)) {
            if (c == '\r') continue;
            std::cout << lkupTable[char2index(c)] << " ";
        }
        fin.close();
    }

}
