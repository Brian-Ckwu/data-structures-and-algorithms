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
  int capacity = 8;
  vector<int> weights = {1, 3, 4, 5};
  vector<int> values = {10, 40, 50, 70};

  cout << knapsack(capacity, weights, values);

  return 0;
}