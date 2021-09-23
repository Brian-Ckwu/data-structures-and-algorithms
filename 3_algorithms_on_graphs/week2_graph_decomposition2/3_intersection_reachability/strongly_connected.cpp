#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<vector<int>>& adj, vector<int>& visited, vector<int>& postorder, int v) {
  visited[v] = 1;
  for (int w : adj[v]) {
    if (visited[w] == 0) {
      dfs(adj, visited, postorder, w);
    }
  }
  postorder.push_back(v);
}

int number_of_strongly_connected_components(vector<vector<int>> adj) {
  // reverse the graph
  int n = adj.size();
  vector<vector<int>> radj(n, vector<int>());
  for (int u = 0; u < n; ++u) {
    for (int v : adj[u]) {
      radj[v].push_back(u);
    }
  }
  // run DFS on the reversed graph and record the post-order
  vector<int> visited(n, 0);
  vector<int> postorder;
  for (int v = 0; v < n; ++v) {
    if (visited[v] == 0) {
      dfs(radj, visited, postorder, v);
    }
  }
  // run DFS from the largest post-order
  fill(visited.begin(), visited.end(), 0);
  reverse(postorder.begin(), postorder.end());
  vector<int> dummy;
  int result = 0;
  for (int v : postorder) {
    if (visited[v] == 0) {
      dfs(adj, visited, dummy, v);
      ++result;
    }
  }
    // an explore == an SCC
  return result;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << number_of_strongly_connected_components(adj);
}
