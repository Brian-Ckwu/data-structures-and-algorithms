#include <iostream>
#include <vector>

using std::vector;

long long get_number_of_inversions(vector<int>& a, vector<int>& b, size_t left, size_t right) {
  long long number_of_inversions = 0;
  if (right <= left + 1) return number_of_inversions;
  size_t ave = left + (right - left) / 2;
  number_of_inversions += get_number_of_inversions(a, b, left, ave);
  number_of_inversions += get_number_of_inversions(a, b, ave, right);
  //write your code here
  return number_of_inversions;
}

long long merge(vector<int>& a, int l, int m, int r) {
  long long count = 0;
  int sub_array_size = r - l + 1;
  vector<int> temp(sub_array_size);
  int i = l;
  int j = m + 1;
  int k = 0;
  while (i <= m && j <= r) {
    if (a[i] <= a[j]) {
      temp[k] = a[i];
      ++i;
    } else { // meaning there is one inversion between a[i...m] and a[j]
      temp[k] = a[j];
      ++j;
      count += (m - i + 1);
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
  return count;
}

long long merge_sort_and_count_inversions(vector<int>& a, int l, int r) {
  if (l >= r)
    return 0;
  long long count = 0;
  int m = (l + r) / 2;
  count += merge_sort_and_count_inversions(a, l, m);
  count += merge_sort_and_count_inversions(a, m + 1, r);
  count += merge(a, l, m, r);
  return count;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  vector<int> b(a.size());
  std::cout << merge_sort_and_count_inversions(a, 0, a.size() - 1) << '\n';
}
