#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

struct Apple
{
    string name;
    double price;
    double weight;
    int countAverage()
    {
        return price / weight;
    }
};

int main(int argc, char* argv[])
{
    Apple best, temp;

    ifstream fin(argv[1]);
    fin >> best.name; fin >> best.price; fin >> best.weight;

    while (fin >> temp.name)
    {
        fin >> temp.price; fin >> temp.weight;
        if (temp.countAverage() < best.countAverage())
            best = temp;
    }

    fin.close();
    cout.precision(2);
    cout.setf(ios::fixed);
    cout << best.name << " " << best.price << " " << best.weight;
}