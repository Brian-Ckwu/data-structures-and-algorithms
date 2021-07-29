#include <bits/stdc++.h>

using namespace std;

int lcs3(vector<int>& a, vector<int>& b, vector<int>& c) {
  // 3D DP array
  int x = a.size();
  int y = b.size();
  int z = c.size();
  int dp[x + 1][y + 1][z + 1];
  // initialize the array
  memset(dp, 0, sizeof(dp));
  // bottom-up filling
  for (int i = 1; i <= x; ++i) {
    for (int j = 1; j <= y; ++j) {
      for (int k = 1; k <= z; ++k) {
        // ins == insertion
        int insx = dp[i - 1][j][k];
        int insy = dp[i][j - 1][k];
        int insz = dp[i][j][k - 1];
        int match = dp[i - 1][j - 1][k - 1] + 1;
        if ((a[i - 1] == b[j - 1]) && (b[j - 1] == c[k - 1])) {
          dp[i][j][k] = match;
        } else {
          dp[i][j][k] = max(max(insx, insy), insz);
        }
      }
    }
  }
  return dp[x][y][z];
}

int main() {
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
