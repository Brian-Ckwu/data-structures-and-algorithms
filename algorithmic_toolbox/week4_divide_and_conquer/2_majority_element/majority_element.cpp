#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int get_majority_element(vector<int>& a, int left, int right) {
  if (left == right) return -1;
  if (left + 1 == right) return a[left];
  //write your code here
  return -1;
}

// Time complexity: O(n); Space complexity: O(n)
int get_majority_element_hash(vector<int>& a) {
  int half_size = a.size() / 2;
  unordered_map<int, int> elem_count;
  for (int i = 0; i < a.size(); ++i) {
    if (elem_count.count(a[i])) {
      ++elem_count[a[i]];
    } else {
      elem_count[a[i]] = 1;
    }
    if (elem_count[a[i]] > half_size) {
      return a[i];
    }
  }
  return -1;
}

// Time complexity: O(nlogn); Space compleixty: O(1)
int get_majority_element_sort(vector<int>& a) {
  sort(a.begin(), a.end());
  int elem = -1;
  int count = 0;
  int half_size = a.size() / 2;
  for (int& i : a) {
    if (i != elem) {
      elem = i;
      count = 1;
    } else {
      ++count;
    }
    if (count > half_size) {
      return i;
    }
  }
  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element_sort(a) != -1) << '\n';
}
