#include <bits/stdc++.h>

using namespace std;

long long distance(vector<vector<int>>& adj, vector<vector<int>>& cost, int s, int t) {
  // containers
  int n = adj.size();
  vector<bool> visited(n, false);
  vector<long long> d(n, LLONG_MAX);
  // initialize starting node
  d[s] = 0;
  // make priority queue
  priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
  for (int i = 0; i < n; ++i) {
    pq.push(make_pair(d[i], i));
  }
  // relaxing the edges
  while (!pq.empty()) {
    int u = pq.top().second; pq.pop(); // ExtractMin
    if (visited[u] == false && d[u] != LLONG_MAX) {
      for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i]; // head node of the edge
        if (d[v] > d[u] + cost[u][i]) {
          d[v] = d[u] + cost[u][i];
          pq.push(make_pair(d[v], v));
        }
      }
    }
    visited[u] = true;
  }
  return (d[t] == LLONG_MAX) ? -1 : d[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
