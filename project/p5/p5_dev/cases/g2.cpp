#include <iostream>
#include <random>
#include <string>
using namespace std;

std::random_device rd;
std::default_random_engine randdd(rd());
int rand(int l, int r) { return randdd() % (r - l + 1) + l; }
int width;
string factor(int depth);
string term(int depth);
string exp(int depth);
string exp(int depth) {
  int len = depth > 0 ? rand(1, width) : 1;
  string temp = term(depth - 1);
  for (int i = 1; i < len; i++)
    temp += (rand(0, 1) ? " +" : " -") + term(depth - 1);
  return temp;
}
string term(int depth) {
  int len = depth > 0 ? rand(1, width) : 1;
  string temp = factor(depth - 1);
  for (int i = 1; i < len; i++)
    temp += (rand(0, 1) ? " *" : " /") + factor(depth - 1);
  return temp;
}
string factor(int depth) {
  if (depth > 0)
    return " (" + exp(depth - 1) + " )";
  else
    return " " + to_string(rand(1, 20));
}
string generate() {
  width = rand(2, 5);
  string res = exp(rand(2, 7)) + " ";
  switch (rand(0, 10)) {
    case 0:
      res += to_string(rand(1, 20));
      break;
    case 1:
      res = res.substr(0, rand(0, res.length() - 1)) + " " +
            res.substr(rand(0, res.length() - 1), res.length() - 1);
      break;
    default:
      break;
  }
  return res;
}
int main() {
  cout << generate() << endl;
  return 0;
}