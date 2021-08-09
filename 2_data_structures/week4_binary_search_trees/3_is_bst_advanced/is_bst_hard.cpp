#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::stack;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool IsBinarySearchTree(const vector<Node>& tree) {
  if (tree.empty())
    return true;
  stack<int> todos;
  int node = 0;
  int prev = -1;
  bool at_right = false;
  while (node != -1 || !todos.empty()) {
    while (node != -1) {
      todos.push(node);
      node = tree[node].left;
    }
    node = todos.top(); todos.pop();
    if (prev != -1 && ((tree[prev].key > tree[node].key) || (!at_right && tree[prev].key >= tree[node].key))) {
      return false;
    }
    prev = node;
    node = tree[node].right;
    if (node != -1) {
      at_right = true;
    } else {
      at_right = false;
    }
  }
  return true;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
