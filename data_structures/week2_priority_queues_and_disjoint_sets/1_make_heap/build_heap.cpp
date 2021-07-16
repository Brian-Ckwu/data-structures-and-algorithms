#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HeapBuilder {
 private:
  vector<int> data_;
  vector<pair<int, int>> swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  // selection sort: O(n^2)
  void GenerateSwapsNaive() {
    swaps_.clear();
    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
  }

  int LeftChild(int i) {
    return (2 * i) + 1;
  }

  int RightChild(int i) {
    return (2 * i) + 2;
  }

  // O(n)
  void GenerateSwaps() {
    // sort_n = first n of elements which need to be
    int sort_n = data_.size() / 2; // how many to be sorted
    // for i = sort_n - 1 to 0:
    for (int i = sort_n - 1; i >= 0; --i) {
      int min_index = i;
      while (min_index <= data_.size() - 1) { // within range
        int original_min = min_index;
        // check left
        if (LeftChild(original_min) <= data_.size() - 1 && data_[min_index] > data_[LeftChild(original_min)])
          min_index = LeftChild(original_min);
        // check right
        if (RightChild(original_min) <= data_.size() - 1 && data_[min_index] > data_[RightChild(original_min)])
          min_index = RightChild(original_min);
        // if the index remain the same, no swap
        if (min_index == original_min)
          break;
        // otherwise swap
        swap(data_[original_min], data_[min_index]);
        swaps_.push_back(make_pair(original_min, min_index));
      }
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
