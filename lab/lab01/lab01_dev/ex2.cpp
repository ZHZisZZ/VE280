/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
using namespace std;


// EFFECTS: return true if the password is a valid one
bool isValidPassword(char password[])
{
    bool alp = false;
    bool dig = false;
    bool oth = false;
    int index = 0;
    int chr;
    while ( (chr = password[index++]) != '\0' )
    {
        if (isalpha(chr))
            alp = true;
        else if (isdigit(chr))
            dig = true;
        else
            oth = true;

        if (alp && dig && oth)
            return true;
    }
    return false;
}


int main()
{
    char password[50] = {};
    cin >> password;
    cout << isValidPassword(password) << endl;
}
