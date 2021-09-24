#include <bits/stdc++.h>

using namespace std;

int distance(vector<vector<int>>& adj, int s, int t) {
  // container (queue for storing nodes & vector for storing distance)
  queue<int> q;
  vector<int> d(adj.size(), -1); // initialize distances to -1
  // initialize starting point
  q.push(s);
  d[s] = 0;
  // fill the distances
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      if (d[v] == -1) { // if node v hasn't been found
        q.push(v);
        d[v] = d[u] + 1;
      }
    }
  }
  return d[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
