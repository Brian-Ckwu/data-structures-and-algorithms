#include <iostream>
#include <vector>
#include <unordered_set>

using std::vector;
using std::pair;
using std::unordered_set;

int explore(vector<vector<int>>& adj, unordered_set<int>& visited, int v) {
  visited.insert(v);
  int cyclic = 0;
  for (int w : adj[v]) {
    if (visited.count(w) == 0) {
      cyclic = explore(adj, visited, w);
    } else {
      return 1;
    }
  }
  return cyclic;
}

int acyclic(vector<vector<int>>& adj, unordered_set<int>& visited) {
  for (int v = 0; v < adj.size(); ++v) {
    if (visited.count(v) == 0) {
      if (explore(adj, visited, v) == 1) {
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  unordered_set<int> visited;
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj, visited);
}
