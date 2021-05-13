#include "binaryTree.h"
#include "huffmanTree.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
//#include <map>


struct Map
{
    std::string code;
    std::string ch;
};
using TableType = std::vector<Map>;

// EFFECTS: construct lookuptable
static void construct_lookupTable(Node *n, TableType &lkupTable, HuffmanTree &tree)
{
    // 到最后一层findpath; 而不是‘a'-'z'遍历
    if (!n->leftSubtree() && !n->rightSubtree()) 
        lkupTable.push_back({tree.findPath(n->getstr()), n->getstr()});
    if (n->leftSubtree())  construct_lookupTable(n->leftSubtree(),  lkupTable, tree);
    if (n->rightSubtree()) construct_lookupTable(n->rightSubtree(), lkupTable, tree);
}

int main(int argc, char *argv[]) 
{
    HuffmanTree tree(argv[1]);
    TableType lkupTable;
    construct_lookupTable(tree.root, lkupTable, tree);
    std::ifstream fin(argv[2]);
    std::string str;
    while (fin >> str) {
        for (auto e : lkupTable) {
            if (e.code == str)
                std::cout << e.ch;
        }
    }
}


// int main(int argc, char *argv[]) {
//     //为什么不让用map, 🤮嘞；
//     HuffmanTree tree("tree.txt");
//     std::map<std::string, char> m;
//     std::string str;
//     for (int i = 97; i <= 122; i++) {
//         str = tree.findPath(std::string(1, char(i)));
//         if (str == "-1") continue;
//         m[str] = char(i);
//     }
//     std::ifstream fin("binary.txt");
//     while (fin >> str) {
//         std::cout << m[str];
//     }
// }
