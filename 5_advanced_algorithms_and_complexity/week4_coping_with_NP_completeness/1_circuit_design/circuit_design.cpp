#include <bits/stdc++.h>

using namespace std;

struct Clause {
  int firstVar;
  int secondVar;
};

struct TwoSatisfiability {
  int numVars;
  vector<Clause> clauses;

  TwoSatisfiability(int n, int m) :
    numVars(n) {
      clauses.resize(m);
    }
  
  int num2id(int num) {
    return (num > 0) ? (num * 2) : (-num * 2 - 1);
  }

  int id2num(int id) {
    return (id % 2 == 0) ? (id / 2) : (-((id + 1) / 2));
  }

  vector<vector<int>> build_impl_graph() {
    int nodes = 2 * numVars;
    vector<vector<int>> G(1 + nodes, vector<int>());
    for (auto& cl : clauses) {
      int num1 = cl.firstVar;
      int num2 = cl.secondVar;
      G[num2id(-num1)].push_back(num2id(num2)); // add edge 1
      G[num2id(-num2)].push_back(num2id(num1)); // add edge 2
    }
    return G;
  }

  void dfs(const vector<vector<int>>& G, vector<int>& visited, vector<int>& postorder, int v) {
    visited[v] = 1;
    for (int w : G[v]) {
      if (visited[w] == 0) {
        dfs(G, visited, postorder, w);
      }
    }
    postorder.push_back(v);
  }

  void dfs_SCC(const vector<vector<int>>& G, vector<int>& visited, vector<int>& SCCs, int v, int index) {
    visited[v] = 1;
    SCCs[v] = index;
    for (int w : G[v]) {
      if (visited[w] == 0) {
        dfs_SCC(G, visited, SCCs, w, index);
      }
    }
  }

  vector<int> build_SCCs(const vector<vector<int>>& G) {
    // build the reverse graph
    int n = G.size();
    vector<vector<int>> Gr(n, vector<int>());
    for (int u = 1; u < n; ++u) {
      for (int v : G[u]) {
        Gr[v].push_back(u);
      }
    }
    // run DFS on the reverse graph to find the SCCs
    vector<int> visited(n, 0);
    vector<int> postorder;
    for (int v = 1; v < n; ++v) {
      if (visited[v] == 0) {
        dfs(Gr, visited, postorder, v);
      }
    }
    // run DFS from the largest post-order
    fill(visited.begin(), visited.end(), 0);
    reverse(postorder.begin(), postorder.end());
    vector<int> SCCs(n); // for recording the SCC indexes
    int index = 1;
    for (int v : postorder) {
      if (visited[v] == 0) {
        dfs_SCC(G, visited, SCCs, v, index);
        ++index;
      }
    }
    return SCCs;
  }

  vector<int> toposort(const vector<vector<int>>& G) {
    int n = G.size();
    vector<int> visited(n, 0);
    vector<int> topo_order;
    for (int v = 1; v < n; ++v) {
      if (visited[v] == 0) {
        dfs(G, visited, topo_order, v);
      }
    }
    reverse(topo_order.begin(), topo_order.end());
    return topo_order;
  }

  bool isSatisfiable(vector<int>& result) {
    vector<vector<int>> G = build_impl_graph();
    vector<int> SCCs = build_SCCs(G);
    int n = G.size();
    for (int i = 1; i < n; i += 2) {
      if (SCCs[i] == SCCs[i + 1]) {
        return false;
      }
    }
    // toposort
    vector<int> topo_order = toposort(G);
    // assign truth values in reverse topological order
    vector<int> truth_values(n, -1);
    for (int i = topo_order.size() - 1; i >= 0; --i) {
      int v = topo_order[i];
      if (truth_values[v] == -1) {
        truth_values[v] = 1;
        if (v % 2 == 0) {
          truth_values[v - 1] = 0;
        } else {
          truth_values[v + 1] = 0;
        }
      }
    }
    // add to result
    for (int i = 1; i < n; ++i) {
      if (truth_values[i] == 1) {
        result.push_back(id2num(i));
      }
    }
    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);

  int n, m;
  cin >> n >> m;
  TwoSatisfiability twoSat(n, m);
  for (int i = 0; i < m; ++i) {
    cin >> twoSat.clauses[i].firstVar >> twoSat.clauses[i].secondVar;
  }

  vector<int> result;
  if (twoSat.isSatisfiable(result)) {
    int r_size = result.size();
    assert(r_size == n);
    cout << "SATISFIABLE" << endl;
    for (int i = 0; i < r_size; ++i) {
      cout << result[i];
      if (i < r_size) {
        cout << " ";
      } else {
        cout << endl;
      }
    }
  } else {
    cout << "UNSATISFIABLE" << endl;
  }

  return 0;
}
