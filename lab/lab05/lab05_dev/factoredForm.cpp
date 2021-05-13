//
// Created by Zhuoer Zhu on 10/06/2020.
//

#include "factoredForm.h"
#include <stdlib.h>

quadraticFunction::quadraticFunction(float a_in, float b_in, float c_in)
{
    // TODO: implement this constructor
    // if a = 0;
    if (!a_in) {
        // if a = b = 0; no solution
        if (!b_in && c_in) {
            r1.imaginary = r2.imaginary = 1;
        }
        else {
            r1.imaginary = r2.imaginary = 0;
            r1.real = r2.real = 0;
        }
        return;
    }
    // a != 0;
    a = a_in;   
    // float b = b_in;
    // float c = c_in;
    int b = b_in;
    int c = c_in;
    float delta = b*b - 4*a*c;
    float sqrt = (delta < 0) ? pow(-delta, 0.5) : pow(delta, 0.5);
    r1.real = r2.real = - b / (2*a);
    if (delta < 0) {
        r1.imaginary = - sqrt / (2*abs(a));
        r2.imaginary = - r1.imaginary;
    }
    else {
        r1.real -= sqrt / (2*abs(a));
        r2.real += sqrt / (2*abs(a));
        r1.imaginary = r2.imaginary = 0;
    }
}

float quadraticFunction::getA() const {
    return a;
}

float quadraticFunction::getB() const {
    // TODO: implement this function
    float ans = -a * (r1.real + r2.real);
    return !ans ? 0 : ans;
}

float quadraticFunction::getC() const {
    // TODO: implement this function
    float ans = a * (r1.real*r2.real - r1.imaginary*r2.imaginary);
    return !ans ? 0 : ans;
}

float quadraticFunction::evaluate(float x) {
    // TODO: implement this function
    float b = getB();
    float c = getC();
    float res = 0;
    res = res + c + b*x + a*x*x;
    return res;
}

root quadraticFunction::getRoot() {
    // TODO: implement this function
    root rt;
    // real number;
    rt.roots[0] = r1; rt.roots[1] = r2;
    if (r1.imaginary)
        rt.realRootNum = 0; 
    else if (r1.real == r2.real)
        rt.realRootNum = 1;
    else 
        rt.realRootNum = 2;
    return rt;
}

int quadraticFunction::intersect(quadraticFunction g) {
    // TODO: implement this function
    quadraticFunction newFunction(getA() - g.getA(), getB() - g.getB(), getC() - g.getC());
    root result = newFunction.getRoot();
    return (result.realRootNum >= 1);
}