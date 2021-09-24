#include <bits/stdc++.h>

using namespace std;

int bipartite(vector<vector<int>>& adj) {
  // containers
  queue<int> q;
  vector<int> color(adj.size(), -1);
  // choose a random starting point
  q.push(0);
  color[0] = 0;
  // color the graph
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      if (color[v] == -1) {
        q.push(v);
        color[v] = (color[u] + 1) % 2;
      } else if (color[v] == color[u]) {
        return 0;
      }
    }
  }
    // check contradiction
  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
