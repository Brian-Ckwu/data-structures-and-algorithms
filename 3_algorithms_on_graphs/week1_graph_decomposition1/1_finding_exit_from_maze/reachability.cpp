#include <iostream>
#include <vector>
#include <unordered_set>

using std::vector;
using std::pair;
using std::unordered_set;


int reach(vector<vector<int>>& adj, unordered_set<int>& visited, int x, int y) {
  visited.insert(x);
  for (int v : adj[x]) {
    if (visited.count(v) == 0) {
      reach(adj, visited, v, y);
    }
  }
  return visited.count(y);
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  // Adjacency list
  vector<vector<int>> adj(n, vector<int>());
  // Hash set for storing visited nodes
  unordered_set<int> visited;
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, visited, x - 1, y - 1);
}
