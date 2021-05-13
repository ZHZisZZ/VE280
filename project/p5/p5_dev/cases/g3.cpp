#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

random_device rd;
default_random_engine randdd(rd());
int rand(int l, int r) { return randdd() % (r - l + 1) + l; }
string random_string(size_t length) {
  auto randchar = []() -> char {
    const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = (sizeof(charset) - 1);
    return charset[rand() % max_index];
  };
  string str(length, 0);
  generate_n(str.begin(), length, randchar);
  return str;
}
int main() {
  cout << endl;
  int cache_size = rand(5, 20), memory_size = rand(20, 40), address;
  cout << cache_size << " " << memory_size << endl;
  vector<int> usedAddress = {rand(0, memory_size - 1), rand(0, memory_size - 1),
                             rand(0, memory_size - 1), rand(0, memory_size - 1),
                             rand(0, memory_size - 1)};
  int loopTime = rand(50, 100);
  for (int i = 0; i != loopTime; ++i) {
    address = rand(0, 3) ? rand(0, memory_size - 1) : usedAddress[rand(0, 4)];
    usedAddress.push_back(address);
    usedAddress.erase(usedAddress.begin());
    //int badInt = rand(0, 9);
    switch (rand(0, 9)) {
      case 0:
      case 1:
      case 2:
      case 3:
        cout << "READ ";
        // if (badInt) cout << address;
        cout << address;
        break;
      case 4:
      case 5:
      case 6:
        cout << "WRITE ";
        cout << address << " ";
        // if (badInt) cout << rand(0, 10000);
        cout << rand(0, 10000);
        break;
      case 7:
        cout << "PRINTCACHE";
        break;
      case 8:
        cout << "PRINTMEM";
        break;
      case 9:
        cout << random_string(rand(5, 10));
        break;
      default:
        break;
    }
    // if (badInt == 0)
    //   cout << (rand(0, 1) ? to_string(rand(0, 10000))
    //                       : random_string(rand(5, 10)));
    cout << endl;
    if (i == loopTime - 2)
      cout << "EXIT" << endl << random_string(rand(5, 10)) << endl;
  }
  return 0;
}
