#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

int search(const vector<int>& a, int low, int high, int x) {
  if (low > high) {
    return -1;
  }

  int mid = low + (high - low) / 2;
  if (a[mid] == x) {
    return mid;
  } else if (a[mid] > x) {
    return search(a, low, mid - 1, x);
  } else {
    return search(a, mid + 1, high, x);
  }
}

int binary_search_recur(const vector<int>& a, int x) {
  int low = 0, high = (int) a.size() - 1;
  return search(a, low, high, x);
}

int binary_search_iter(const vector<int>& a, int x) {
  int low = 0;
  int high = (int) a.size() - 1;

  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (a[mid] == x) {
      return mid;
    } else if (a[mid] > x) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return -1;
}

int linear_search(const vector<int>& a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    std::cout << binary_search_iter(a, b[i]) << ' ';
  }
}
