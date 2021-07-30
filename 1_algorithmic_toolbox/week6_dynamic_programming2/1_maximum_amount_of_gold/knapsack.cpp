#include <bits/stdc++.h>

using namespace std;

// initial implementation
int optimal_weight(int W, const vector<int>& w) {
  // Vector for storing maximum values of subproblems
  // Rows: number of items allowed to be used; columns: the capacity of the knapsack
  int rows = w.size() + 1;
  int cols = W + 1;
  vector<int> max_weights(rows * cols);

  // Initialize the values in the 2D array
  for (int item = 0; item < rows; ++item) {
    max_weights[item * cols + 0] = 0;
  }
  for (int wt = 0; wt < cols; ++wt) {
    max_weights[0 * cols + wt] = 0;
  }

  // DP Algo: filling the max_values row by row (is it okay to fill column by column?)
  int wt_with_item = 0;
  for (int item = 1; item < rows; ++item) {
    for (int wt = 1; wt < cols; ++wt) {
      max_weights[item * cols + wt] = max_weights[(item - 1) * cols + wt];
      if (w[item - 1] <= wt) { // Note that we should use "i - 1" to access the ith item;
        wt_with_item = max_weights[(item - 1) * cols + (wt - w[item - 1])] + w[item - 1];
        if (max_weights[item * cols + wt] < wt_with_item) {
          max_weights[item * cols + wt] = wt_with_item;
        }
      }
    }
  }
  // Reconstruct optimal solution (not yet implemented)

  return max_weights[rows * cols - 1];
}

// another iterative (bottom-up / tabulation) DP
int optimal_weight_iter(int W, const vector<int>& w) {
  // DP table
  int n = w.size();
  vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0)); // initialize to zeros
  // fill the DP table
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= W; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (j - w[i - 1] >= 0) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i - 1]] + w[i - 1]);
      }
    }
  }
  return dp[n][W];
}

// recursive (top-down / memoization) DP
int optimal(int i, int W, const vector<int>& w, vector<vector<int>>& dp) {
  if (dp[i][W] != -1)
    return dp[i][W];
  int max_weight = optimal(i - 1, W, w, dp);
  if (w[i - 1] <= W)
    max_weight = max(max_weight, optimal(i - 1, W - w[i - 1], w, dp) + w[i - 1]);
  return (dp[i][W] = max_weight);
}

int optimal_weight_recur(int W, const vector<int>& w) {
  // for memoization
  int n = w.size();
  vector<vector<int>> dp(n + 1, vector<int>(W + 1, -1));
  // initialize the first row and the first column to zeros
  dp[0][0] = 0;
  for (int i = 1; i <= n; ++i) {
    dp[i][0] = 0;
  }
  for (int j = 1; j <= W; ++j) {
    dp[0][j] = 0;
  }
  return optimal(n, W, w, dp);
} 

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight_recur(W, w) << '\n';
}
