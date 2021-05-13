/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
using namespace std;


// EFFECTS: return the trace of the Laplacian of the weight matrix.
int traceLaplacian(int weight[][50], int size)
{
    // TODO: Implement this function.
    int trace = 0;
    for (int r = 0; r < size; r++)
    {
        trace -= weight[r][r];
        for (int c = 0; c < size; c++) 
        {
            trace += weight[r][c]; 
        }
    }
    return trace;
}


int main()
{
    int size, trace;
    int weight[50][50] = {};
    cin >> size;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            cin >> weight[i][j];
        }
    }
    trace = traceLaplacian(weight, size);
    cout << trace << endl;
}