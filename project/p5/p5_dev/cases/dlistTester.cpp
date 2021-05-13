#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "dlist.h"

using namespace std;

int main() {
  string lineBuffer, op;
  istringstream iss;
  vector<Dlist<int>*> dlists;
  vector<int*> values;
  int value, index;
  int* valPtr;
  while (getline(cin, lineBuffer)) {
    if (lineBuffer.empty()) continue;
    iss.clear();
    iss.str(lineBuffer);
    cout << lineBuffer << endl;
    iss >> op;
    if (op == "newDlist") {
      dlists.push_back(new Dlist<int>());
    } else if (op == "copyDlist") {
      iss >> index;
      dlists.push_back(new Dlist<int>(*dlists[index]));
    } else if (op == "assignDlist") {
      auto&& tmp = new Dlist<int>;
      *tmp = *dlists[index];
      dlists.push_back(tmp);
    } else if (op == "isEmpty") {
      iss >> index;
      cout << dlists[index]->isEmpty() << endl;
    } else if (op == "insertFront") {
      iss >> index >> value;
      values.push_back(new int(value));
      dlists[index]->insertFront(values.back());
    } else if (op == "insertBack") {
      iss >> index >> value;
      values.push_back(new int(value));
      dlists[index]->insertBack(values.back());
    } else if (op == "removeFront") {
      iss >> index;
      valPtr = dlists[index]->removeFront();
      cout << *valPtr << endl;
      delete valPtr;
    } else if (op == "removeFront") {
      iss >> index;
      valPtr = dlists[index]->removeBack();
      cout << *valPtr << endl;
      delete valPtr;
    }
  }
  for (auto&& l : dlists) delete l;
  return 0;
}
