#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool in_order_check(const vector<Node>& tree, int i, long long& prev, bool& is_valid) {
  if (!is_valid)
    return false;
  if (i == -1)
    return true;
  in_order_check(tree, tree[i].left, prev, is_valid);
  if (prev > (long long) tree[i].key)
    return is_valid = false;
  prev = (long long) tree[i].key;
  in_order_check(tree, tree[i].right, prev, is_valid);
  return is_valid;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  if (tree.empty())
    return true;
  long long prev = LLONG_MIN;
  bool is_valid = true;
  return in_order_check(tree, 0, prev, is_valid);
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
