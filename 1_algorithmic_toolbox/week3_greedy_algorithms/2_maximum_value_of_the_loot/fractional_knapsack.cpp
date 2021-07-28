#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
  double weight;
  double value;
};

bool by_wv_ratio(const Item& x, const Item& y) {
  return (x.value / x.weight) > (y.value / y.weight);
}

double get_optimal_value(int capacity, const vector<int>& weights, const vector<int>& values) {
  // Value to return
  double value = 0.0;
  // Vector of items
  vector<Item> items(weights.size());
  for (int i = 0; i < weights.size(); ++i) {
    items[i].weight = weights[i];
    items[i].value = values[i];
  }

  // Sort the items according to value/weight ratio
  sort(items.begin(), items.end(), by_wv_ratio);

  // Fill the knapsack from the first item to the last item
  for (const Item& item : items) {
    if (capacity > item.weight) {
      value += item.value;
      capacity -= item.weight;
    } else {
      value += capacity * (item.value / item.weight);
      capacity -= capacity; // This line is not necessary in practice, though
      break;
    }
  }

  return value;
}

int main() {
  int n;
  int capacity;
  cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  cout.precision(10);
  cout << optimal_value << endl;
  return 0;
}
