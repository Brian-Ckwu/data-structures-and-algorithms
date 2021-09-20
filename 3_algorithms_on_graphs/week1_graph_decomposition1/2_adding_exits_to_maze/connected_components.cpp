#include <iostream>
#include <vector>
#include <unordered_set>

using std::vector;
using std::pair;
using std::unordered_set;

void explore(vector<vector<int>>& adj, unordered_set<int>& visited, int v) {
  visited.insert(v);
  for (int w : adj[v]) {
    if (visited.count(w) == 0) {
      explore(adj, visited, w);
    }
  }
}

int number_of_components(vector<vector<int>>& adj, unordered_set<int>& visited) {
  int res = 0;
  for (int v = 0; v < adj.size(); ++v) {
    if (visited.count(v) == 0) {
      explore(adj, visited, v);
      ++res;
    }
  }
  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>()); // adjacency list
  unordered_set<int> visited; // for storing visited vertices
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj, visited);
}
