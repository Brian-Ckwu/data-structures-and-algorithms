#include <bits/stdc++.h>
#include <chrono>

using namespace std;

/*
  Comparison-based algorithms:
    1. O(n^2):
      Selection sort
      Insertion sort
      Bubble sort
    2. O(nlogn):
      Merge sort
      Quick sort
      Heap sort
*/
// O(n^2) algorithms
// selection_sort
vector<int> selection_sort(vector<int>& a) {
  for (int i = 0; i < a.size(); ++i) {
    int min_index = i;
    for (int j = i + 1; j < a.size(); ++j) {
      if (a[j] < a[min_index])
        min_index = j;
    }
    swap(a[i], a[min_index]);
  }
  return a;
}

// insertion_sort
vector<int> insertion_sort(vector<int>& a) {
  for (int i = 1; i < a.size(); ++i) {
    int key = a[i]; // must store key because a[i] will be changed in the loop
    int j = i - 1;
    while (j >= 0 && a[j] > key) {
      a[j + 1] = a[j];
      --j;
    }
    a[j + 1] = key;
  }
  return a;
}

// O(nlogn) algorithms
// merge_sort
void merge(vector<int>& a, int l, int m, int r) {
  int sub_array_size = r - l + 1;
  vector<int> temp(sub_array_size);
  int i = l;
  int j = m + 1;
  int k = 0;
  while (i <= m && j <= r) {
    if (a[i] <= a[j]) {
      temp[k] = a[i];
      ++i;
    } else {
      temp[k] = a[j];
      ++j;
    }
    ++k;
  }
  // copy the remaining array to the temp array
  while (i <= m) {
    temp[k] = a[i];
    ++i;
    ++k;
  }
  while (j <= r) {
    temp[k] = a[j];
    ++j;
    ++k;
  }
  // copy the temp array to a[l:r+1]
  for (int i = 0; i < temp.size(); ++i) {
    a[l + i] = temp[i];
  }
}

void merge_sort(vector<int>& a, int l, int r) {
  if (l >= r)
    return;
  int m = (l + r) / 2;
  merge_sort(a, l, m);
  merge_sort(a, m + 1, r);
  merge(a, l, m, r);
}

vector<int> merge_sort_wrapper(vector<int>& a) {
  int l = 0;
  int r = a.size() - 1;
  merge_sort(a, l, r);
  return a;
}

// randomized_quick_sort3
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

vector<int> quick_sort_wrapper(vector<int>& a) {
  int l = 0;
  int r = a.size() - 1;
  randomized_quick_sort_3(a, l, r);
  return a;
}

/*
  Non-comparison-based algorithms:
    Counting sort (O(n + k))
*/

/*
  Testing functions
*/
vector<int> gen_array(int n, double m = 1.0) { // n == array length, m == multiplying factor
  vector<int> a(n);
  int cardinality = n * m;
  for (int i = 0; i < n; ++i) {
    a[i] = rand() % cardinality;
  }
  return a;
}

void print_array(const vector<int>& a) {
  for (const auto& i : a) {
    cout << i << " ";
  }
}

bool is_same_array(vector<int>& a, vector<int>& b) {
  assert(a.size() == b.size());
  for (int i = 0; i < a.size(); ++i) {
    if (a[i] != b[i])
      return false;
  }
  return true;
}

template <typename F>
double sorting_time(F sort_func, vector<int>& a) {
  auto start = chrono::high_resolution_clock::now();
  sort_func(a);
  auto end = chrono::high_resolution_clock::now();
  double execution_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
  return execution_time;
}

template <typename F1, typename F2>
void stress_test(int cases, int n, double m, F1 sort_func1, F2 sort_func2) {
  for (int c = 0; c < cases; ++c) {
    cout << "Test #" << c + 1 << endl;
    // generate test case
    vector<int> a1 = gen_array(n, m);
    vector<int> a2(a1);
    // sorting
    double t1 = sorting_time(sort_func1, a1);
    double t2 = sorting_time(sort_func2, a2);
    // display results
    if (is_same_array(a1, a2)) {
      cout << "***Same answers!***" << endl;
      cout << "sort_func1(): " << t1 << " ms" << endl;
      cout << "sort_func2(): " << t2 << " ms" << endl;
    } else {
      cout << "---Wrong answers!---" << endl;
      cout << "sort_func1(): "; print_array(a1); cout << endl;
      cout << "sort_func2(): "; print_array(a2); cout << endl;
      break;
    }
  }
}

int main() {
  stress_test(10, 100000, 1, merge_sort_wrapper, quick_sort_wrapper);

  return 0;
}