#include <bits/stdc++.h>

using namespace std;

int negative_cycle(vector<vector<int>>& adj, vector<vector<int>>& cost) {
  // container
  int n = adj.size();
  vector<int> d(n, 1000000000);
  d[0] = 0;
  // iterate n times
  int has_cycle = 0;
  for (int i = 0; i < n; ++i) {
    has_cycle = 0;
    // relax each edge (u, v)
    for (int u = 0; u < n; ++u) {
      for (int j = 0; j < adj[u].size(); ++j) {
        int v = adj[u][j];
        int w = cost[u][j];
        if (d[v] > d[u] + w) {
          d[v] = d[u] + w;
          has_cycle = 1;
        }        
      }
    }
  }
  return has_cycle;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  vector<vector<int>> cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
