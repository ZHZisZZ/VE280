#include <iostream>
using namespace std;

const int UPBOUND = 10000000;


// EFFECTS: return true if the input is valid; the input is valid 
//          if the first input is [1, 4], and the second is [1, 10000000];
bool validInput(int first, int second);

// EFFECTS: return true if the number is a Triangle number;
bool checkTri(int num);

// EFFECTS: return true if the number is a Palindrome number;
bool checkPal(int num);

// EFFECTS: return true if the number is a Power number;
bool checkPow(int num);

// EFFECTS: return true if the number is a Abundant number;
bool checkAbu(int num);

int main()
{
    int first, second;
    cout << "Please enter the integer and the test number: ";
    // Prompt untill the valid combination is entered.
    while (!(cin >> first >> second) || ! validInput(first, second))
    {
        cout << "Please enter the integer and the test number: ";
    }
    switch(second)
    {
        case 1: cout << checkTri(first) << endl; break;
        case 2: cout << checkPal(first) << endl; break;
        case 3: cout << checkPow(first) << endl; break;
        case 4: cout << checkAbu(first) << endl; break;
    }

}

bool validInput(int first, int second)
{
    return first > 0 && first <= UPBOUND && second > 0 && second < 5;
}

bool checkTri(int num)
{
    int inc = 2;
    int sum = 1;
    while (sum < num)
    {
        sum += inc++;
    }
    return sum == num;
}


bool checkPal(int num)
{
    if (!(num % 10)) return false;
    int rev = 0;
    while (rev < num)
    {
        rev  = 10 * rev + num % 10;
        num /= 10;
    }
    return rev == num || rev / 10 == num;
}

bool checkPow(int num)
{
    if (num == 1) return true;
    for (int i = 2; i*i <= num; i++)
    {
        /* if i can divide num, then i could not be the m */
        if (num % i) continue;
        int multi = i * i;
        while (multi < num)
        {
            multi *= i;
        }
        if (multi == num) return true;
    }
    return false;
}

bool checkAbu(int num)
{
    int sum = 1;
    int i = 2;
    for (; i*i < num; i++)
    {
        if (!(num % i))
        {
            sum += i;
            sum += num / i;
        }
    }
    if (i*i == num) sum += i;
    return sum > num;
}