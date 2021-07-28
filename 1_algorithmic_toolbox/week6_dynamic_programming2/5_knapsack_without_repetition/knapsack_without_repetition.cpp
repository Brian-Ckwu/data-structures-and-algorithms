#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

struct TestCase {
  int capacity;
  vector<int> weights;
  vector<int> values;
  int max_value;
};

// Iterative algorithm
int knapsack_iter(int capacity, const vector<int>& weights, const vector<int>& values) {
  // 2D array for storing maximum values of subproblems
  // Rows: number of items allowed to be used; columns: the capacity of the knapsack
  int rows = weights.size() + 1;
  int columns = capacity + 1;
  int max_values[rows][columns];

  // Initialize the values in the 2D array
  for (int row = 0; row < rows; ++row) {
    max_values[row][0] = 0;
  }
  for (int column = 0; column < columns; ++column) {
    max_values[0][column] = 0;
  }

  // DP Algo: filling the max_values row by row (is it okay to fill column by column?)
  int item_weight = 0;
  int value_with_item = 0;
  for (int i = 1; i < rows; ++i) {
    item_weight = weights[i - 1];
    for (int w = 1; w < columns; ++w) {
      max_values[i][w] = max_values[i - 1][w];
      if (item_weight <= w) {
        value_with_item = max_values[i - 1][w - item_weight] + values[i - 1];
        if (max_values[i][w] < value_with_item) {
          max_values[i][w] = value_with_item;
        }
      }
    }
  }

  // Reconstruct optimal solution (not yet implemented)

  return max_values[rows - 1][columns - 1];
}

// Recursive algorithm using hashmap
int knapsack_recur(int, const vector<int>&, const vector<int>&);

// Manual test
void manual_test() {
  vector<TestCase> testcases = {
    {10, {6, 3, 4, 2}, {30, 14, 16, 9}, 46},
    {50, {10, 20, 30}, {60, 100, 120}, 220},
    {100, {18, 42, 88, 3}, {114, 136, 192, 223}, 473},
    {100, {27, 2, 41, 1, 25, 1, 34, 3, 50, 12}, {38, 86, 112, 0, 66, 97, 195, 85, 42, 223}, 798}
  };

  for (TestCase testcase : testcases) {
    assert(knapsack_iter(testcase.capacity, testcase.weights, testcase.values) == testcase.max_value);
    cout << "OK" << "\n";
  }
}


int main() {
  // Test
  manual_test();
  
  return 0;
}