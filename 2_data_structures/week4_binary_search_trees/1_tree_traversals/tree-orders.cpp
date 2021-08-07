#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;
using std::stack;

class TreeOrders {
  int n;
  vector<int> key;
  vector<int> left;
  vector<int> right;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

  void push_nodes_in_order(vector<int>& result, int index) {
    if (index == -1)
      return;
    push_nodes_in_order(result, left[index]);
    result.push_back(key[index]);
    push_nodes_in_order(result, right[index]);
  }

  vector<int> in_order() {
    vector<int> result;
    push_nodes_in_order(result, 0);
    return result;
  }

  vector<int> in_order_iter() {
    vector<int> res;
    stack<int> nodes;
    int node = 0;
    while (node != -1 || !nodes.empty()) {
      while (node != -1) {
        nodes.push(node);
        node = left[node];
      }
      node = nodes.top(); nodes.pop();
      res.push_back(key[node]);
      node = right[node];
    }
    return res;
  }

  void push_nodes_pre_order(vector<int>& result, int index) {
    if (index == -1)
      return;
    result.push_back(key[index]);
    push_nodes_pre_order(result, left[index]);
    push_nodes_pre_order(result, right[index]);
  }

  vector<int> pre_order() {
    vector<int> result;
    push_nodes_pre_order(result, 0);
    return result;
  }

  vector<int> pre_order_iter() {
    vector<int> res;
    stack<int> nodes;
    int node = 0;
    while (node != -1 || !nodes.empty()) {
      while (node != -1) {
        res.push_back(key[node]);
        nodes.push(right[node]);
        node = left[node];
      }
      node = nodes.top(); nodes.pop();
    }
    return res;
  }

  void push_nodes_post_order(vector<int>& result, int index) {
    if (index == -1)
      return;
    push_nodes_post_order(result, left[index]);
    push_nodes_post_order(result, right[index]);
    result.push_back(key[index]);
  }

  vector<int> post_order() {
    vector<int> result;
    push_nodes_post_order(result, 0);
    return result;
  }

  vector<int> post_order_iter() {
    vector<int> res;
    stack<int> nodes;
    int node = 0;
    int visited_node = -1;
    while (node != -1 || !nodes.empty()) {
      while (node != -1) {
        nodes.push(node);
        node = left[node];
      }
      node = nodes.top();
      if (right[node] == -1 || right[node] == visited_node) { // crucial step: check if visited
        res.push_back(key[node]);
        nodes.pop();
        visited_node = node;
        node = -1;
      } else {
        node = right[node];
      }
    }
    return res;
  }
};

void print(vector<int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order_iter());
  print(t.pre_order_iter());
  print(t.post_order_iter());
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

