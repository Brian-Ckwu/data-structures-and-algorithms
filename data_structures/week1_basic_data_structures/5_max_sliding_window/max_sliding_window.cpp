#include <iostream>
#include <vector>
#include <map>

using namespace std;

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

// O(nlogn) solution?
vector<int> max_sliding_window_map(const vector<int>& A, int w) {
  vector<int> outputs;
  map<int, int> window;

  // initialize the map and add the maximum element into output vector
  for (int i = 0; i < w; ++i) {
    int num = A[i];
    if (window.find(num) == window.end()) { // element not found
      window[num] = 1;
    } else {
      window[num] += 1;
    }
  }
  outputs.push_back(window.rbegin()->first);

  // start sliding the window
  for (int i = w; i < A.size(); ++i) {
    int oldn = A[i - w];
    int newn = A[i];

    // handle old
    window[oldn] -= 1;
    if (window[oldn] == 0) {
      window.erase(oldn);
    }
    // handle new
    if (window.find(newn) == window.end()) {
      window[newn] = 1;
    } else {
      window[newn] += 1;
    }

    outputs.push_back(window.rbegin()->first);
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

  const vector<int> outputs = max_sliding_window_map(A, w);
  for (int output: outputs) {
    cout << output << " ";
  }

  return 0;
}
