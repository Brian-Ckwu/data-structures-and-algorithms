#include <bits/stdc++.h>

using namespace std;

struct Edge {
  int from;
  int to;
};

struct ConvertHampathToSat {
  int numVertices;
  int numEdges;
  vector<Edge> edges;

  ConvertHampathToSat(int n, int m) :
    numVertices(n),
    numEdges(m) {
      edges.resize(m);
    }
  
  int toIndex(int i, int j) {
    return (i - 1) * numVertices + j;
  }

  void fill_edges(set<pair<int, int>>& s) {
    for (Edge& edge : edges) {
      s.insert(make_pair(edge.from, edge.to));
      s.insert(make_pair(edge.to, edge.from));
    }
  }

  void printEquisatisfiableSatFormula() {
    int n = numVertices;
    // record the edges in the set container s
    set<pair<int, int>> s;
    fill_edges(s);
    // 0. output the number of clauses and variables
    int C = 2 * (n + n * n * (n - 1) / 2) + (n * n - s.size()) * (n - 1);
    int V = n * n;
    cout << C << ' ' << V << endl;
    // 1. each vertex belongs to a path
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <=n; ++j) {
        cout << toIndex(i, j) << ' ';
      }
      cout << 0 << endl;
    }
    // 2. each vertex appears just once in a path
    for (int i = 1; i <= n; ++i) {
      for (int k = 1; k <= n - 1; ++k) {
        for (int l = k + 1; l <= n; ++l) {
          cout << -toIndex(i, k) << ' ' << -toIndex(i, l) << ' ' << 0 << endl;
        }
      }
    }
    // 3. each position in a path is occupied by some vertex
    for (int j = 1; j <= n; ++j) {
      for (int i = 1; i <= n; ++i) {
        cout << toIndex(i, j) << ' ';
      }
      cout << 0 << endl;
    }
    // 4. no two vertices occupy the same position of a path
    for (int j = 1; j <= n; ++j) {
      for (int k = 1; k <= n - 1; ++k) {
        for (int l = k + 1; l <= n; ++l) {
          cout << -toIndex(k, j) << ' ' << -toIndex(l, j) << ' ' << 0 << endl;
        }
      }
    }
    // 5. if not connected by an edge, two vertices should not be adjacent in the path
    for (int i1 = 1; i1 <= n; ++i1) {
      for (int i2 = 1; i2 <= n; ++i2) {
        if (s.count(make_pair(i1, i2)) == 0) {
          for (int k = 1; k <= n - 1; ++k) {
            cout << -toIndex(i1, k) << ' ' << -toIndex(i2, k + 1) << ' ' << 0 << endl;
          }
        }
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);

  int n, m;
  cin >> n >> m;
  ConvertHampathToSat converter(n, m);
  for (int i = 0; i < m; ++i) {
    cin >> converter.edges[i].from >> converter.edges[i].to;
  }

  converter.printEquisatisfiableSatFormula();

  return 0;
}
