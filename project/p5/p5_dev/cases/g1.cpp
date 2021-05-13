#include <iostream>
#include <random>
#include <vector>

using namespace std;

random_device rd;

int main() {
  cout << endl;
  int numDlists = rd() % 5 + 2;
  for (int i = 0; i != numDlists; ++i) {
    cout << "newDlist" << endl;
    cout << "isEmpty " << i << endl;
    int numFront = rd() % 10 + 5, numBack = rd() % 10 + 5;
    for (int j = 0; j != numBack - 1; ++j)
      cout << "insertBack " << i << " " << (rd() % 10) << endl;
    for (int j = 0; j != numFront - 1; ++j)
      cout << "insertFront " << i << " " << (rd() % 10) << endl;
    cout << "insertBack " << i << " " << (rd() % 10) << endl;
    cout << "insertFront " << i << " " << (rd() % 10) << endl;
    cout << "isEmpty " << i << endl;
    cout << "removeFront " << i << endl;
    cout << "removeBack " << i << endl;
  }
  int i = numDlists;
  cout << "newDlist" << endl;
  cout << "isEmpty " << i << endl;
  int numDigits = rd() % 20 + 10;
  for (int j = 0; j != numDigits; ++j)
    cout << "insertBack " << i << " " << (rd() % 10) << endl;
  for (int j = 0; j != numDigits; ++j) cout << "removeFront " << i << endl;
  cout << "isEmpty " << i << endl;
  cout << "insertFront " << i << " " << (rd() % 10) << endl;
  cout << "insertBack " << i << " " << (rd() % 10) << endl;
  cout << "isEmpty " << i << endl;
  cout << "removeFront " << i << endl;
  cout << "removeFront " << i << endl;
  cout << "isEmpty " << i << endl;
  for (int j = 0; j != numDigits; ++j)
    cout << "insertFront " << i << " " << (rd() % 10) << endl;
  for (int j = 0; j != numDigits; ++j) cout << "removeBack " << i << endl;
  cout << "isEmpty " << i << endl;
  cout << "insertFront " << i << " " << (rd() % 10) << endl;
  cout << "insertBack " << i << " " << (rd() % 10) << endl;
  cout << "isEmpty " << i << endl;
  for (int i = 0; i != numDlists; ++i)
    cout << (rd() % 2 ? "assignStack " : "copyStack ") << i << endl;
  return 0;
}