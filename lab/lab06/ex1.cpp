#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

// constants used
#define MAX_NUM_NODE 1000
#define MAX_NUM_CHILD 10
#define SIZE_TAB 4

// forward declaration of classes
class ASTNode;
class ProgramNode;
class DeclListNode;
class DeclNode;
class VarDeclNode;
class FnDeclNode;
class FormalDeclNode;
class FormalsListNode;
class FnBodyNode;
class StmtListNode;
class TypeNode;
class IntNode;
class BoolNode;
class VoidNode;
class StmtNode;
class AssignStmtNode;
class PostIncStmtNode;
class PostDecStmtNode;
class ExpNode;
class IntLitNode;
class TrueNode;
class FalseNode;
class IdNode;
class AssignNode;

// **********************************************************************
// ASTNode class (base class for all other kinds of nodes)
// **********************************************************************

class ASTNode {
   public:
    ASTNode(int n = 0) : num_child(n) {}
    virtual ~ASTNode(){};

    int numChild() {
        return num_child;
    }

    void setChild(int index, ASTNode* ptr) {
        children[index] = ptr;
    }

    void addIndent(int indent) {
        for (int i = 0; i < indent; ++i) {
            cout << " ";
        }
    }

    virtual void unparse(int indent) = 0;

   protected:
    int num_child;
    ASTNode* children[MAX_NUM_CHILD];
};

// **********************************************************************
// ProgramNode,  DeclListNode, FormalsListNode, FnBodyNode, StmtListNode
// **********************************************************************

class ProgramNode : public ASTNode {
   public:
    ProgramNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent) {
        children[0]->unparse(indent);  // unparse DeclListNode
    }
};

class DeclListNode : public ASTNode {
   public:
    DeclListNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent) {
        for (int i = 0; i < num_child; ++i) {
            children[i]->unparse(indent);  // unparse DeclNode
        }
    }
};

class FormalsListNode : public ASTNode {
   public:
    FormalsListNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent) {
        // TODO
        for (int i = 0; i < num_child; ++i) {
            children[i]->unparse(indent);
            if (i != num_child-1) {
                cout << ", ";
            }
        }
    }
};

class FnBodyNode : public ASTNode {
   public:
    FnBodyNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent) {
        // TODO, think about what indent value to pass to its children!
        for (int i = 0; i < num_child; ++i) {
            children[i]->unparse(indent + SIZE_TAB);
        }
    }
};

class StmtListNode : public ASTNode {
   public:
    StmtListNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent) {
        // TODO
        for (int i = 0; i < num_child; ++i) {
            children[i]->unparse(indent);
        }
    }
};

// **********************************************************************
// DeclNode and its subclasses
// **********************************************************************

class DeclNode : public ASTNode {
   public:
    DeclNode(int n = 0) : ASTNode(n) {}

    virtual void unparse(int indent) = 0;
};

class VarDeclNode : public DeclNode {
   public:
    VarDeclNode(int n = 0) : DeclNode(n) {}

    void unparse(int indent) {
        // TODO
        for (int i = 0; i < indent; i++) {
            cout << " ";
        }
        children[0]->unparse(indent);
        cout << " ";
        children[1]->unparse(indent);
        cout << ";\n";
    }
};

class FnDeclNode : public DeclNode {
   public:
    FnDeclNode(int n = 0) : DeclNode(n) {}

    void unparse(int indent) {
        addIndent(indent);
        children[0]->unparse(indent);  // unparse TypeNode
        cout << " ";
        children[1]->unparse(indent);  // unparse IdNode
        cout << "(";
        children[2]->unparse(indent);  // unparse FormalsListNode
        cout << ") {" << endl;
        children[3]->unparse(indent);  // unparse FnBodyNode
        addIndent(indent);
        cout << "}" << endl;
    }
};

class FormalDeclNode : public DeclNode {
   public:
    FormalDeclNode(int n = 0) : DeclNode(n) {}

    void unparse(int indent) {
        // TODO
        children[0]->unparse(indent);
        cout << " ";
        children[1]->unparse(indent);
    }
};

// **********************************************************************
// TypeNode and its Subclasses
// **********************************************************************

class TypeNode : public ASTNode {
   public:
    TypeNode(int n = 0) : ASTNode(n) {}

    virtual void unparse(int indent) = 0;
};

class IntNode : public TypeNode {
   public:
    IntNode(int n = 0) : TypeNode(n) {}

    void unparse(int indent) {
        // TODO
        cout << "int";
    }
};

class BoolNode : public TypeNode {
   public:
    BoolNode(int n = 0) : TypeNode(n) {}

    void unparse(int indent) {
        // TODO
        cout << "bool";
    }
};

class VoidNode : public TypeNode {
   public:
    VoidNode(int n = 0) : TypeNode(n) {}

    void unparse(int indent) {
        // TODO
        cout << "void";
    }
};

// **********************************************************************
// StmtNode and its subclasses
// **********************************************************************

class StmtNode : public ASTNode {
   public:
    StmtNode(int n = 0) : ASTNode(n) {}

    virtual void unparse(int indent) = 0;
};

class AssignStmtNode : public StmtNode {
   public:
    AssignStmtNode(int n = 0) : StmtNode(n) {}

    void unparse(int indent) {
        // TODO
        for (int i = 0; i < indent; i++) {
            cout << " ";
        }
        children[0]->unparse(indent);
        cout << ";\n";
    }
};

class PostIncStmtNode : public StmtNode {
   public:
    PostIncStmtNode(int n = 0) : StmtNode(n) {}

    void unparse(int indent) {
        // TODO
        for (int i = 0; i < indent; i++) {
            cout << " ";
        }
        children[0]->unparse(indent);
        cout << "++;\n";
    }
};

class PostDecStmtNode : public StmtNode {
   public:
    PostDecStmtNode(int n = 0) : StmtNode(n) {}

    void unparse(int indent) {
        // TODO
        for (int i = 0; i < indent; i++) {
            cout << " ";
        }
        children[0]->unparse(indent);
        cout << "--;\n";
    }
};

// **********************************************************************
// ExpNode and its subclasses
// **********************************************************************

class ExpNode : public ASTNode {
   public:
    ExpNode(int n = 0) : ASTNode(n) {}

    virtual void unparse(int indent) = 0;
};

class IntLitNode : public ExpNode {
   public:
    IntLitNode(int n = 0, int val = 0) {
        num_child = n;
        myVal = val;
    }

    void unparse(int indent) {
        // TODO
        cout << myVal;
    }

   private:
    int myVal;
};

class TrueNode : public ExpNode {
   public:
    TrueNode(int n = 0) : ExpNode(n) {}

    void unparse(int indent) {
        // TODO
        cout << "true";
    }
};

class FalseNode : public ExpNode {
   public:
    FalseNode(int n = 0) : ExpNode(n) {}

    void unparse(int indent) {
        // TODO
        cout << "false";
    }
};

class IdNode : public ExpNode {
   public:
    IdNode(int n = 0, string str = "") {
        num_child = n;
        myName = str;
    }

    virtual void unparse(int indent) {
        // TODO
        cout << myName;
    }

   private:
    string myName;
};

class AssignNode : public ExpNode {
   public:
    AssignNode(int n = 0) : ExpNode(n) {}

    void unparse(int indent) {
        // TODO
        children[0]->unparse(indent);
        cout << " = ";
        children[1]->unparse(indent);
    }
};


void getInput(ASTNode* nodes[], int nodesNum);

int main() {

    // TODO: read input line by line, allocate new node, store into array
    int nodesNum;
    ASTNode* nodes[MAX_NUM_NODE];
    cin >> nodesNum;
    getInput(nodes, nodesNum);

    // TODO: traverse array to construct the tree
    queue<ASTNode*> que;
    int index = 0;
    que.push(nodes[0]);
    for (int i = 1; i < nodesNum; i++) {
        que.front()->setChild(index++, nodes[i]);
        if (index == que.front()->numChild()) {
            que.pop();
            index = 0;
        }
        if (nodes[i]->numChild()) 
            que.push(nodes[i]);
    }

    // call unparse() of root to print whole program
    ASTNode* root = nodes[0];
    root->unparse(0);

    // TODO: delete the allocated nodes
    for (int i = 0; i < nodesNum; i++) {
        delete nodes[i];
    }

}


void getInput(ASTNode* nodes[], int nodesNum) 
{
    string nodeName;
    int    childNum;

    for (int i = 0; i < nodesNum; i++) {
        cin >> nodeName;
        cin >> childNum;
        if (nodeName == "ProgramNode")
            nodes[i] = new ProgramNode(childNum);
        else if (nodeName == "DeclListNode")
            nodes[i] = new DeclListNode(childNum);
        else if (nodeName == "VarDeclNode")
            nodes[i] = new VarDeclNode(childNum);
        else if (nodeName == "FnDeclNode")
            nodes[i] = new FnDeclNode(childNum);
        else if (nodeName == "FormalDeclNode")
            nodes[i] = new FormalDeclNode(childNum);
        else if (nodeName == "FormalsListNode")  
            nodes[i] = new FormalsListNode(childNum);
        else if (nodeName == "FnBodyNode")  
            nodes[i] = new FnBodyNode(childNum);
        else if (nodeName == "StmtListNode")  
            nodes[i] = new StmtListNode(childNum);
        // TypeNode:
        else if (nodeName == "IntNode")
            nodes[i] = new IntNode(childNum);
        else if (nodeName == "BoolNode")
            nodes[i] = new BoolNode(childNum);
        else if (nodeName == "VoidNode")
            nodes[i] = new VoidNode(childNum);
        // StmtNode;
        else if (nodeName == "AssignStmtNode")
            nodes[i] = new AssignStmtNode(childNum);
        else if (nodeName == "PostIncStmtNode")
            nodes[i] = new PostIncStmtNode(childNum);
        else if (nodeName == "PostDecStmtNode")
            nodes[i] = new PostDecStmtNode(childNum);
        // ExpNode
        else if (nodeName == "IntLitNode") {
            int value;
            cin >> value;
            nodes[i] = new IntLitNode(childNum, value);
        }
        else if (nodeName == "TrueNode")
            nodes[i] = new TrueNode(childNum);
        else if (nodeName == "FalseNode")
            nodes[i] = new FalseNode(childNum);
        else if (nodeName == "IdNode") {
            string Id;
            cin >> Id;
            nodes[i] = new IdNode(childNum, Id);
        }
        else if (nodeName == "AssignNode")
            nodes[i] = new AssignNode(childNum);
    }
}