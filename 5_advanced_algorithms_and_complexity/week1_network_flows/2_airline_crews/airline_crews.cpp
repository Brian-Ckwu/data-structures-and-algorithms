#include <bits/stdc++.h>

using namespace std;

class MaxMatching {
 public:
  void Solve() {
    vector<vector<bool>> adj_matrix = ReadData();
    vector<int> matching = FindMatching(adj_matrix);
    WriteResponse(matching);
  }

 private:
  vector<vector<bool>> ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
    for (int i = 0; i < num_left; ++i) {
      for (int j = 0; j < num_right; ++j) {
        int bit;
        cin >> bit;
        adj_matrix[i][j] = (bit == 1);
      }
    }
    return adj_matrix;
  }

  void WriteResponse(const vector<int>& matching) {
    for (int i = 0; i < matching.size(); ++i) {
      if (i > 0)
        cout << " ";
      if (matching[i] == -1)
        cout << "-1";
      else
        cout << (matching[i] + 1);
    }
    cout << "\n";
  }

  void construct_residual_network(vector<unordered_map<int, bool>>& Gf, const vector<vector<bool>>& adj_matrix) {
    int n = adj_matrix.size();
    int m = adj_matrix[0].size();
    for (int i = 0; i < n; ++i) {
      int l_node = i + 1;
      Gf[0][l_node] = true; // connect the root node to the left nodes
      Gf[l_node][0] = false;
      for (int j = 0; j < m; ++j) {
        int r_node = n + j + 1;
        if (Gf[r_node].empty()) { // connect the right nodes to the end node
          Gf[r_node][n + m + 1] = true;
        }
        if (adj_matrix[i][j]) {
          Gf[l_node][r_node] = true; // forward edge
          Gf[r_node][l_node] = false; // backward edge
        }
      }
    }
  }

  bool DFS(const vector<unordered_map<int, bool>>& Gf, vector<bool>& visited, vector<int>& path, int u, int t) {
    if (u == t) {
      path.push_back(t);
      return true;
    }
    visited[u] = true;
    path.push_back(u);
    for (auto& p : Gf[u]) {
      if (p.second) {
        int v = p.first;
        if (!visited[v]) {
          if (DFS(Gf, visited, path, v, t))
            return true;
        }
      }
    }
    path.pop_back();
    return false;
  }

  void update_residual_network(vector<unordered_map<int, bool>>& Gf, const vector<int>& path) {
    int p = path.size();
    for (int i = 0; i < p - 1; ++i) {
      int u = path[i], v = path[i + 1];
      Gf[u][v] = false; // update forward edge
      Gf[v][u] = true; // update backward edge
    }
  }

  void update_matching(vector<int>& matching, const vector<int>& path, int num_left) {
    int p = path.size();
    for (int i = 1; i < p - 1; i += 2) {
      matching[path[i] - 1] = path[i + 1] - 1 - num_left;
    }
  }

  vector<int> FindMatching(const vector<vector<bool>>& adj_matrix) {
    // Replace this code with an algorithm that finds the maximum
    // matching correctly in all cases.
    int num_left = adj_matrix.size();
    int num_right = adj_matrix[0].size();
    vector<int> matching(num_left, -1);
    vector<unordered_map<int, bool>> Gf(num_left + num_right + 2);
    construct_residual_network(Gf, adj_matrix);
    int n = Gf.size();
    while (true) {
      vector<int> path;
      vector<bool> visited(n, false);
      DFS(Gf, visited, path, 0, n - 1);
      if (path.empty()) {
        break;
      }
      update_residual_network(Gf, path);
      update_matching(matching, path, num_left);
    }
    return matching;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  MaxMatching max_matching;
  max_matching.Solve();
  return 0;
}
