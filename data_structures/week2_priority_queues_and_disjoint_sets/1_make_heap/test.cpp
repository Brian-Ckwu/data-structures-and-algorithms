/*
  test std::make_heap
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  vector<int> v = {4, 1, 7, 18, 3, 6, 0, 11, 14, 5};
  make_heap(v.begin(), v.end());

  // sort heap
  for (int i = 0; i < v.size(); ++i) {
    pop_heap(v.begin(), v.end() - i);
  }

  for (int& i : v) {
    cout << i << " ";
  }

  return 0;
}