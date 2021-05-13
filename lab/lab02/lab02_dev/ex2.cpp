/*
 * Lab2 Ex2 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <cstdlib>
#include <iostream>

using namespace std;

#define MNAM 16
#define MSTU 10
#define SNUM 3

typedef struct {
    // TODO: complete struct
    enum COURSE { Chinese, Math, English };
    char name[MNAM];
    int score[SNUM];
    int sumScore;
    void calSumScore()
    {
        sumScore = 0;
        for (int i = 0; i < SNUM; i++)
        {
            sumScore += score[i];
        }
    }
} Student;

int compare(const void* p1, const void* p2) 
{
    // TODO: complete compare function for qsort()
    return ((Student*)p1)->sumScore < ((Student*)p2)->sumScore ? 1 : -1;
}

int main() 
{
    int nStudent;

    // TODO: read input
    cin >> nStudent;
    Student* spt = new Student[nStudent];
    for (int i = 0; i < nStudent; i++)
    {
        cin >> spt[i].name;
        for (int j = 0; j < SNUM; j++)
        {
            cin >> spt[i].score[j];
        } 
        spt[i].calSumScore();
    }

    // TODO: sort array with qsort()
    qsort(spt, nStudent, sizeof(Student), compare);

    // TODO: print result
    for (int i = 0; i < nStudent; i++)
    {
        cout << spt[i].name << " ";
        for (int j = 0; j < SNUM; j++)
        {
            cout << spt[i].score[j] << " ";
        }
        cout << endl;
    }
    delete [] spt;
    return 0;
}