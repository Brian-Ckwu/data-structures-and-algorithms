#include <bits/stdc++.h>

using namespace std;

double minimum_distance(vector<int> x, vector<int> y) {
  // containers
  int n = x.size();
  vector<double> cost(n, 100000000);
  cost[0] = 0;
  priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
  vector<bool> visited(n, false);
  // make queue
  for (int i = 0; i < n; ++i) {
    pq.push(make_pair(cost[i], i));
  }
  // Prim's algorithm
  while (!pq.empty()) {
    int u = pq.top().second; pq.pop(); // add node u to MST
    if (!visited[u]) {
      visited[u] = true;
      for (int v = 0; v < n; ++v) { // traverse each edge
        if (!visited[v]) {
          double dist = sqrt(pow(x[u] - x[v], 2) + pow(y[u] - y[v], 2));
          if (cost[v] > dist) {
            cost[v] = dist;
            pq.push(make_pair(dist, v));
          }
        }
      }
    }
  }
  return accumulate(cost.begin(), cost.end(), 0.0);
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
