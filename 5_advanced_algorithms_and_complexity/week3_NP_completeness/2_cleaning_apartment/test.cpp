#include <iostream>
#include <set>

using namespace std;

int main() {
  set<pair<int, int>> s;
  s.insert(make_pair(1, 2));
  s.insert(make_pair(1, 3));

  cout << s.count(make_pair(1, 1)) << endl;
  cout << s.count(make_pair(1, 3)) << endl;

  return 0;
}