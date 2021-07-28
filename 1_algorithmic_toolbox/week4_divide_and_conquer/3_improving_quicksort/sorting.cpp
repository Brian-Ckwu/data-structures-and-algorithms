#include <bits/stdc++.h>

using namespace std;

int partition2(vector<int>& a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

pair<int, int> partition3(vector<int>& a, int l, int r) {
  int p = a[l]; // pivot element
  int m1 = l;
  int m2 = l;
  for (int i = l + 1; i <= r; ++i) {
    if (a[i] < p) {
      ++m1;
      ++m2;
      if (i > m2) {
        swap(a[m1], a[m2]);
      }
      swap(a[m1], a[i]);
    } else if (a[i] == p) {
      ++m2;
      swap(a[m2], a[i]);
    } else {
      // do nothing
    }
  }
  swap(a[l], a[m1]);
  return make_pair(m1, m2);
}

void randomized_quick_sort_2(vector<int>& a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1); // random pivot
  swap(a[l], a[k]);
  int m = partition2(a, l, r); // partition2 or partition3

  randomized_quick_sort_2(a, l, m - 1);
  randomized_quick_sort_2(a, m + 1, r);
}

void randomized_quick_sort_3(vector<int>& a, int l, int r) {
  if (l >= r)
    return;
  // choose a random pivot
  int k = l + rand() % (r - l + 1); // (r - l + 1) == number of elements
  swap(a[l], a[k]);
  pair<int, int> m = partition3(a, l, r);
  // recursive call to quicksort
  randomized_quick_sort_3(a, l, m.first - 1);
  randomized_quick_sort_3(a, m.second + 1, r);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort_3(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
