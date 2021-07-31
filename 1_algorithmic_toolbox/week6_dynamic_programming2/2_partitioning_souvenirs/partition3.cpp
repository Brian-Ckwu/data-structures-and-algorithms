#include <bits/stdc++.h>

using namespace std;

// my first implementation
void extend(vector<int>& A, vector<vector<bool>>& dp, int m, int n, vector<vector<int>>& solutions, vector<int>& sol) {
  if (dp[m][n] == false)
    return;
  if (n == 0) {
    solutions.push_back(sol);
    return;
  }
  extend(A, dp, m - 1, n, solutions, sol);
  if (A[m - 1] <= n && dp[m - 1][n - A[m - 1]]) { // if extendable
    sol.push_back(A[m - 1]);
    extend(A, dp, m - 1, n - A[m - 1], solutions, sol);
    sol.pop_back();
  }
}

vector<vector<int>> reconstruct_solutions(vector<int>& A, vector<vector<bool>>& dp) {
  vector<vector<int>> solutions;
  int m = dp.size() - 1;
  int n = dp[0].size() - 1;
  vector<int> sol;
  extend(A, dp, m, n, solutions, sol); // DFS
  return solutions;
}

bool partition2(vector<int>& A) {
  int sum = accumulate(A.begin(), A.end(), 0);
  int m = A.size();
  int n = sum / 2;
  vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
  for (int i = 0; i <= m; ++i) {
    dp[i][0] = true;
  }
  for (int i = 1; i <= m; ++i) {
    int cumsum = accumulate(A.begin(), A.begin() + i, 0);
    int n_max = min(cumsum, n);
    for (int j = 1; j <= n_max; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (A[i - 1] <= j)
        dp[i][j] = (dp[i][j] || dp[i - 1][j - A[i - 1]]);
    }
  }
  return dp[m][n];
}

bool partition3(vector<int>& A) {
  // check if the sum can be divided by 3
  int sum = accumulate(A.begin(), A.end(), 0);
  if (sum % 3 != 0)
    return 0;
  // boolean dp table (is it possible to make up weight w with first i items)
  int m = A.size();
  int n = sum * 2 / 3;
  vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
  // initialize the dp table
  for (int i = 0; i <= m; ++i) {
    dp[i][0] = true;
  }
  // fill dp up to 2/3 sum
  for (int i = 1; i <= m; ++i) {
    int cumsum = accumulate(A.begin(), A.begin() + i, 0);
    int n_max = min(cumsum, n);
    for (int j = 1; j <= n_max; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (A[i - 1] <= j)
        dp[i][j] = (dp[i][j] || dp[i - 1][j - A[i - 1]]);
    }
  }
  // reconstruct solutions
  vector<vector<int>> solutions = reconstruct_solutions(A, dp);
  for (auto& sol : solutions) {
    if (partition2(sol))
      return true;
  }
  return false;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}
