//
// Created by Zhuoer Zhu on 10/06/2020.
//

#include <cmath>
#include "standardForm.h"
#include <cstdlib>

quadraticFunction::quadraticFunction(float a_in, float b_in, float c_in)
    : a(a_in), b(b_in), c(c_in) {}
// TODO: implement this constructor

float quadraticFunction::getA() const {
    return a;
}

float quadraticFunction::getB() const {
    return b;
}

float quadraticFunction::getC() const {
    return c;
}

float quadraticFunction::evaluate(float x) {
    // TODO: implement this function
    return c + b*x + a*x*x;
}

root quadraticFunction::getRoot() {
    // TODO: implement this function
    root rt;
    // if a = 0;
    if (!a) {
        // if a = b = 0 and c! = 0 -> no solution
        if (!b && c) {
            rt.realRootNum = 0;
        }
        else {
            rt.realRootNum = 1; // 1 or 2 does not matter.
        }
        return rt;
    }
    // a != 0;
    float delta = b*b - 4*a*c;
    float sqrt = (delta < 0) ? pow(-delta, 0.5) : pow(delta, 0.5);
    rt.roots[0].real = rt.roots[1].real = - b / (2*a);
    if (delta < 0)
    {
        rt.realRootNum = 0;
        rt.roots[0].imaginary = - sqrt / (2*abs(a));
        rt.roots[1].imaginary = - rt.roots[0].imaginary;
    }
    else
    {
        if (delta == 0) rt.realRootNum = 1;
        else rt.realRootNum = 2;
        rt.roots[0].real -= sqrt / (2*abs(a));
        rt.roots[1].real += sqrt / (2*abs(a));
        rt.roots[0].imaginary = rt.roots[1].imaginary = 0;
    }
    return rt;
}

int quadraticFunction::intersect(quadraticFunction g){
    // TODO: implement this function
    quadraticFunction newFunction(a - g.getA(), b - g.getB(), c - g.getC());
    root result = newFunction.getRoot();
    return (result.realRootNum >= 1);
}