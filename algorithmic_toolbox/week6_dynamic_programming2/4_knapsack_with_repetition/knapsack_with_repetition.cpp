#include <iostream>
#include <vector>

using namespace std;

int knapsack(int capacity, const vector<int>& weights, const vector<int>& values) {
  // Vector for storing maximum values
  vector<int> max_values(capacity + 1, 0);

  // DP Algo
  int value = 0;
  for (int i = 1; i <= capacity; ++i) {
    for (int j = 0; j < weights.size(); ++j) {
      if (i - weights[j] >= 0) {
        value = max_values[i - weights[j]] + values[j];
        if (value > max_values[i]) {
          max_values[i] = value;
        }
      }
    }
  }

  return max_values[capacity];
}

int main() {
  // Test the case from the course
  int capacity = 10;
  vector<int> weights = {6, 3, 4, 2};
  vector<int> values = {30, 14, 16, 9};

  cout << knapsack(capacity, weights, values);

  return 0;
}