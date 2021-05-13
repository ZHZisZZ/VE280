/*
 * This is an exercise of VE280 Lab 10, SU2020.
 * Written by Martin Ma.
 * Latest Update: 7/17/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 *
 * Correct Output:
 *
        12345678
        87654321
 *
 *
 */

#include <iostream>
#include "my_stack.h"
#include "my_stack_impl.h"

int main()
{
    try{
        Stack<int> s;
        s.push(1);
        s.push(2);
        s.print();
    }
    catch(stackEmpty){
        std::cout << "Oops, looks like I'm empty!\n";
    }
    return 0;
}

// int main()
// {
//     Stack<int> s1, s2, s3;
//     s1.push(4);
//     s1.push(3);
//     s1.push(2);
//     s1.push(1);
//     s1.print();
    
//     s2.push(7);
//     s2.push(6);
//     s2.push(5);
//     s2.print();

//     s3 = s1 + s2;
//     s3.print();
// }
