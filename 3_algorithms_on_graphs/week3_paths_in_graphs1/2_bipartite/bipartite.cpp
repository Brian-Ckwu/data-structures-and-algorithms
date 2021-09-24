#include <bits/stdc++.h>

using namespace std;

int bipartite(vector<vector<int>>& adj) {
  int n = adj.size();
  // containers
  queue<int> q;
  vector<int> color(n, -1);
  // loop through each connected component
  for (int s = 0; s < n; ++s) {
    if (color[s] == -1) {
      // choose a random starting point
      q.push(s);
      color[s] = s;
      // color the graph
      while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
          if (color[v] == -1) {
            q.push(v);
            color[v] = (color[u] + 1) % 2;
          } else if (color[v] == color[u]) { // check contradiction
            return 0;
          }
        }
      }
    }
  }
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
