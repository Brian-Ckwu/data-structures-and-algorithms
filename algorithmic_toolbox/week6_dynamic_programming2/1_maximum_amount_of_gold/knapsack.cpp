#include <iostream>
#include <vector>

using namespace std;

// Could the algorithm be different 
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

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
