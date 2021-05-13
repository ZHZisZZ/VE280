/*
 * Lab2 Ex1 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <iostream>

using namespace std;

#define RANGE 100000
#define MLEN 21

bool isPrime[RANGE + 1];
int  arr[MLEN];

// MODIFIES: isPrime[]
// EFFECTS: fill in isPrime[], true for prime, false otherwise
void generateIsPrime() 
{
    for (int i = 0; i <= RANGE; i++) 
    { 
        isPrime[i] = true; 
    }
    isPrime[0] = isPrime[1] = false;
    // the current prime number;
    int cPrime = 2; 

    while (cPrime != RANGE + 1) 
    {
        for (int i = cPrime * 2; i <= RANGE; i += cPrime) 
        { 
            isPrime[i] = false; 
        }
        for (cPrime++; cPrime <= RANGE && !isPrime[cPrime]; cPrime++) { continue; }
    }
}

int main() 
{

    generateIsPrime();
    int len;
    cin >> len;
    int temp;
    for (int i = 0; i < len; i++)
    {
        cin >> temp;
        if (isPrime[temp]) cout << temp << " ";
    }
    return 0;
}