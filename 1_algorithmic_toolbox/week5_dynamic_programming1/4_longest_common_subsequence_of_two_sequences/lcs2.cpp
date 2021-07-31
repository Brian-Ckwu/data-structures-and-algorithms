#include <bits/stdc++.h>

using namespace std;

int lcs2(vector<int>& a, vector<int>& b) {
  // matrix for storing alignment score
  int rows = a.size() + 1;
  int cols = b.size() + 1;
  int as[rows][cols];
  // initialize matrix for the first row and the firsts column
  as[0][0] = 0;
  for (int row = 1; row < rows; ++row) {
    as[row][0] = 0;
  }
  for (int col = 1; col < cols; ++col) {
    as[0][col] = 0;
  }
  // fill the DP matrix
  for (int row = 1; row < rows; ++row) {
    for (int col = 1; col < cols; ++col) {
      int ins = as[row][col - 1];
      int del = as[row - 1][col];
      int match = as[row - 1][col - 1] + 1;
      if (a[row - 1] == b[col - 1]) {
        as[row][col] = match;
      } else {
        as[row][col] = max(ins, del);
      }
    }
  }
  return as[rows - 1][cols - 1];
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
