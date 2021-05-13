#include <iostream>
#include <cstdlib>
#include <limits.h>
#include <string.h>
using namespace std;

int main(int argc, char* argv[])
{
    bool flagMan  = false;
    bool flagVer  = false;
    bool flagAdd  = false;
    bool flagSma  = false;
    int  addNum;

    /* parse argument */
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "--help"))
            flagMan = true;
        else if (!strcmp(argv[i], "--verbose"))
            flagVer = true;
        else if (!strcmp(argv[i], "--add"))
            flagAdd = true;
        else 
        {
            flagSma = true;
            addNum = atoi(argv[++i]);
        }
    }

    /* output */
    if (flagMan)
        cout << "Hey, I love Integers.\n";
    else if (!flagAdd && !flagSma)
        cout << "No work to do!\n";
    else 
    {
        int len, sum(0), leastNum(INT_MAX), tempNum(0);
        cin >> len;
        for (int i = 0; i < len; i++)
        {
            cin >> tempNum;
            sum += tempNum;
            leastNum = (leastNum < tempNum) ? leastNum : tempNum;
        }
        if (flagAdd)
        {
            if (flagVer) cout << "This is add operation.\n";
            cout << sum << endl;
        }
        if (flagSma)
        {   
            if (flagVer) cout << "This is small operation.\n";
            cout << addNum + leastNum << endl;
        }
    }
        
}