#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

// O(nm) naive solution
vector<int> max_sliding_window_naive(const vector<int>& A, int w) {
  vector<int> outputs(A.size() - w + 1);
  
  int window_max = 0;
  for (size_t i = 0; i < A.size() - w + 1; ++i) {
    window_max = A[i];
    for (size_t j = i + 1; j < i + w; ++j)
      window_max = max(window_max, A[j]);
  
    outputs[i] = window_max;
  }

  return outputs;
}

// O(n) solution
vector<int> max_sliding_window_fast(const vector<int>& A, int w);


int main() {
  int n = 0;
  cin >> n;

  vector<int> A(n);
  for (size_t i = 0; i < n; ++i)
    cin >> A.at(i);

  int w = 0;
  cin >> w;

  const vector<int> outputs = max_sliding_window_naive(A, w);
  for (int output: outputs) {
    cout << output << " ";
  }

  return 0;
}
