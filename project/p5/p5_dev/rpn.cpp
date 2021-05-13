#include <iostream>
#include <sstream>
#include "dlist.h"
#include <string>

template <class T>
class Stack
{
private:
    Dlist<T> list;
public:
    // EFFECTS: //
    void push(T op) { list.insertBack(new T(op)); }

    // EFFECTS: //
    T pop()
    {
        T *last = list.removeBack();
        T lastV = *last;
        delete last;
        return lastV;
    }

    // EFFECTS: //
    T top()
    {
        T *last = list.removeBack();
        list.insertBack(last);
        return *last;
    }

    // EFFECTS: //
    bool empty() const { return list.isEmpty(); }
};

// EFFECTS: //
enum class ERROR {PARENTHSES_MISMATCH, NOT_ENOUGH_OPERANDS, DIVIDE_BY_ZERO, TOO_MANY_OPERANDS};

// EFFECTS: //
bool GreaterEqual(char c1, char c2)
{
    return c1 == '*' || c1 == '/' || ((c1 == '+' || c1 == '-') && (c2 == '-' || c2 == '+') );
}

// EFFECTS: //
int calculate(int n1, int n2, char op)
{
    if (op == '+') return n1 + n2;
    if (op == '-') return n1 - n2;
    if (op == '*') return n1 * n2;
    if (!n2) throw ERROR::DIVIDE_BY_ZERO;
    return n1 / n2;
}

// EFFECTS: //
void infix2postfix(std::stringstream &postFix)
{
    Stack<char> opStack;
    std::string token;
    getline(std::cin, token);
    std::stringstream sin(token);
    while (sin >> token) {
        if (token[0] >= '0' && token[0] <= '9') {
            postFix << token << " ";
        } else if (token[0] == '(') {
            opStack.push(token[0]);
        } else if (token[0] == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postFix << opStack.pop() << " ";
            }
            if (opStack.empty()) throw ERROR::PARENTHSES_MISMATCH;
            opStack.pop();
        } else {    // a operator
            while (!opStack.empty()      &&
                    opStack.top() != '(' &&
                    GreaterEqual(opStack.top(), token[0]) ) {
                postFix << opStack.pop() << " ";
            }
            opStack.push(token[0]);
        }
    }
    while (!opStack.empty()) {
        char op = opStack.pop();
        if (op == '(') throw ERROR::PARENTHSES_MISMATCH;
        postFix << op << " ";
    }
}

// EFFECTS: //
int main()
{
    std::stringstream postFix;
    Stack<int> intStack;
    std::string temp;
    int result;

    try {
        infix2postfix(postFix);
        std::cout << postFix.str() << std::endl;
        while (postFix >> temp) {
            if (temp[0] >= '0' && temp[0] <= '9') {
                intStack.push(atoi(temp.c_str()));
            } else {
                int n1, n2;
                if (intStack.empty()) throw ERROR::NOT_ENOUGH_OPERANDS;
                n2 = intStack.pop();
                if (intStack.empty()) throw ERROR::NOT_ENOUGH_OPERANDS;
                n1 = intStack.pop();
                intStack.push(calculate(n1, n2, temp[0]));
            }
        }
        // or throw not enough
        if (intStack.empty())throw ERROR::NOT_ENOUGH_OPERANDS;
        result = intStack.pop();
        if (!intStack.empty()) throw ERROR::TOO_MANY_OPERANDS;
        std::cout << result << std::endl;
    } catch (ERROR e) {
        std::string errorInfo[4] = {"Parenthesis mismatch", "Not enough operands", "Divide by zero", "Too many operands"};
        std::cout << "ERROR: " << errorInfo[(int)e] << std::endl;
    }
}

//void infix2postfix(std::stringstream &postFix)
//{
//    Stack<char> opStack;
//    std::string token;
//    getline(std::cin, token);
//    std::stringstream sin(token);
//    while (sin >> token) {
//        if (token[0] >= '0' && token[0] <= '9') {
//            postFix << token << " ";
//        } else if (token[0] == '(') {
//            opStack.push(token[0]);
//        } else if (token[0] == ')') {
//            while (!opStack.empty() && opStack.top() != '(') {
//                postFix << opStack.pop() << " ";
//            }
//            if (opStack.empty()) throw ERROR::PARENTHSES_MISMATCH;
//            opStack.pop();
//        } else {    // a operator
//            while (!opStack.empty()      &&
//                   opStack.top() != '(' &&
//                   GreaterEqual(opStack.top(), token[0]) ) {
//                postFix << opStack.pop() << " ";
//            }
//            opStack.push(token[0]);
//        }
//    }
//
////    while (!opStack.empty()) {
////        char op = opStack.pop();
////        if (op == '(') throw ERROR::PARENTHSES_MISMATCH;
////        postFix << op << " ";
////    }
//    if (!opStack.empty()) {
//        char op = opStack.pop();
//        if (op == '(') throw ERROR::PARENTHSES_MISMATCH;
//        postFix << op;
//    }
//    while (!opStack.empty()) {
//        postFix << " ";
//        char op = opStack.pop();
//        if (op == '(') throw ERROR::PARENTHSES_MISMATCH;
//        postFix << op;
//    }
//}
//
//int main()
//{
//    for (int i = 0; i < 1018; i++) {
//        std::stringstream postFix;
//        Stack<int> intStack;
//        std::string temp;
//        int result;
//        try {
//            infix2postfix(postFix);
//            std::cout << postFix.str() << std::endl;
//            while (postFix >> temp) {
//                if (temp[0] >= '0' && temp[0] <= '9') {
//                    intStack.push(atoi(temp.c_str()));
//                } else {
//                    int n1, n2;
//                    if (intStack.empty()) throw ERROR::NOT_ENOUGH_OPERANDS;
//                    n2 = intStack.pop();
//                    if (intStack.empty()) throw ERROR::NOT_ENOUGH_OPERANDS;
//                    n1 = intStack.pop();
//                    intStack.push(calculate(n1, n2, temp[0]));
//                }
//            }
//            // "( ) as input.txt"
//            if (intStack.empty()) throw ERROR::NOT_ENOUGH_OPERANDS;
//            result = intStack.pop();
//            if (!intStack.empty()) throw ERROR::TOO_MANY_OPERANDS;
//            std::cout << result << std::endl;
//        } catch (ERROR e) {
//            std::string errorInfo[4] = {"Parenthesis mismatch", "Not enough operands", "Divide by zero", "Too many operands"};
//            std::cout << "ERROR: " << errorInfo[(int)e] << std::endl;
//        }
//    }
//}