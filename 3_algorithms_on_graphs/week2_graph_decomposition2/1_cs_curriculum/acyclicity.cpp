#include <iostream>
#include <vector>
#include <unordered_set>

using std::vector;
using std::pair;
using std::unordered_set;

int check_cyclic(vector<vector<int>>& adj, unordered_set<int>& visited, unordered_set<int>& removed, int v) {
  visited.insert(v);
  int cyclic = 0;
  for (int w : adj[v]) {
    if (removed.count(w) == 0) {
      if (visited.count(w) == 1) {
        cyclic = 1;
      } else {
        cyclic = check_cyclic(adj, visited, removed, w);
      }
    }
    if (cyclic)
      break;
  }
  removed.insert(v);
  return cyclic;
}

int acyclic(vector<vector<int>>& adj, unordered_set<int>& visited, unordered_set<int>& removed) {
  for (int v = 0; v < adj.size(); ++v) {
    if (visited.count(v) == 0 && check_cyclic(adj, visited, removed, v) == 1) {
      return 1;
    }
  }
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  unordered_set<int> visited;
  unordered_set<int> removed;
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj, visited, removed);
}
