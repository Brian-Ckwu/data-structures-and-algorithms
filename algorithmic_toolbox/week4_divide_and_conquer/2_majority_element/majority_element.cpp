#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

bool is_major(int elem, vector<int>& a, int left, int right) {
  int half_size = (right - left) / 2;
  int count = 0;
  for (int i = left; i < right; ++i) {
    if (a[i] == elem) {
      ++count;
    }
  }
  if (count > half_size)
    return true;
  return false;
}

// Time complexity: O(nlogn)
int get_majority_element_dnc(vector<int>& a, int left, int right) {
  if (left == right) return -1;
  if (left + 1 == right) return a[left];
  int mid = (left + right) / 2;
  int lres = get_majority_element_dnc(a, left, mid);
  int rres = get_majority_element_dnc(a, mid, right);
  if (lres == rres) { // either -1 == -1 or majority == majority
    return lres;
  } else { // one of the half has the majority -> count if the majority > half_size
    if (lres != -1 && is_major(lres, a, left, right)) {
      return lres;
    }
    if (rres != -1 && is_major(rres, a, left, right)) {
      return rres;
    }
    return -1;
  }
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
  std::cout << (get_majority_element_dnc(a, 0, a.size()) != -1) << '\n';
}
