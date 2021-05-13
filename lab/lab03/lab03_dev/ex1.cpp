/*
 * VE280 Lab 3, SU2020.
 * Written by Guoxin Yin
 */

#include <iostream>

using namespace std;

const int MAXSIZE = 10;
const int TARGET = 280;


bool canWin(int count, int arr[], int position) {
    // EFFECTS: return whether the player can win given the start position
    // and the card sequence
    if (position < 0 || position >= count || !arr[position]) return false;
    if (arr[position] == TARGET) return true;
    int step = arr[position];
    arr[position] = 0;
    return canWin(count, arr, position + step) ||
           canWin(count, arr, position - step);
    // TODO: implement this function
}

int main() {
    int count;
    cin >> count;
    int arr[MAXSIZE];
    for (int i = 0; i < count; ++i) {
        cin >> arr[i];
    }
    int position;
    cin >> position;
    cout << canWin(count, arr, position);
}