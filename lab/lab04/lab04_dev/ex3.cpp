#include <string>
#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    string temp;
    stringstream sin, ss;
    int cnt = 0;

    getline(cin, temp);
    sin << temp;

    while (sin >> temp)
    {
        ss.clear();
        ss << temp;
        temp.clear();
        while (getline(ss, temp, ','))
        {
            if (!temp.empty())
            {
                cout << temp << endl;
                cnt++;
            }
        }
    }

    cout << cnt << endl;
}