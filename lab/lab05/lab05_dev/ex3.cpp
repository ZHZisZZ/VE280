//
// Created by Zhuoer Zhu on 10/06/2020.
//
#include "factoredForm.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main() {
    float a1, b1, c1, x;
    float a2, b2, c2;

    while (cin >> a1) {
        cin >> b1 >> c1 >> x;
        cin >> a2 >> b2 >> c2;

        quadraticFunction f(a1, b1, c1);
        quadraticFunction g(a2, b2, c2);

        cout << setprecision(1) << fixed;
        cout << "f(x)=" << f.getA() << "x^2+" << f.getB() << "x+" << f.getC() << endl;
        cout << "f(" << x << ")=" << f.evaluate(x) << endl;

        cout << setprecision(1) << fixed;
        cout << "g(x)=" << g.getA() << "x^2+" << g.getB() << "x+" << g.getC() << endl;
        cout << "g(" << x << ")=" << g.evaluate(x) << endl;

        root root1 = f.getRoot();
        cout << "f(x) has " << root1.realRootNum << " real roots." << endl;
        cout << "x1 = " << root1.roots[0].real << " + " << root1.roots[0].imaginary << "i" << endl;
        cout << "x2 = " << root1.roots[1].real << " + " << root1.roots[1].imaginary << "i" << endl;

        cout << f.intersect(g) << std::endl << std::endl;
    }
}