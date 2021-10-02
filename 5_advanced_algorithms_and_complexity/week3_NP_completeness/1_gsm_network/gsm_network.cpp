#include <ios>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  int from;
  int to;
};

struct ConvertGSMNetworkProblemToSat {
  int numVertices;
  vector<Edge> edges;

  ConvertGSMNetworkProblemToSat(int n, int m) :
    numVertices(n) {
      edges.resize(m);
    }

  void printEquisatisfiableSatFormula() {
    // variables: 3 * k + 0/1/2 (where 0 <= k <= n - 1)
    int C = 4 * numVertices + 3 * edges.size();
    int V = 3 * numVertices;
    cout << C << ' ' << V << endl;
    // one vertex has exactly one color
    for (int k = 0; k < numVertices; ++k) {
      int c1 = 1 + 3 * k + 0, c2 = 1 + 3 * k + 1, c3 = 1 + 3 * k + 2;
      cout << c1 << ' ' << c2 << ' ' << c3 << ' ' << 0 << endl;
      cout << -c1 << ' ' << -c2 << ' ' << 0 << endl;
      cout << -c1 << ' ' << -c3 << ' ' << 0 << endl;
      cout << -c2 << ' ' << -c3 << ' ' << 0 << endl;
    }
    // no adjacent vertices have the same color
    for (Edge& edge : edges) {
      int u = 1 + 3 * (edge.from - 1), v = 1 + 3 * (edge.to - 1);
      cout << -(u + 0) << ' ' << -(v + 0) << ' ' << 0 << endl;
      cout << -(u + 1) << ' ' << -(v + 1) << ' ' << 0 << endl;
      cout << -(u + 2) << ' ' << -(v + 2) << ' ' << 0 << endl;
    }
  }
};

int main() {
  ios::sync_with_stdio(false);

  int n, m;
  cin >> n >> m;
  ConvertGSMNetworkProblemToSat converter(n, m);
  for (int i = 0; i < m; ++i) {
    cin >> converter.edges[i].from >> converter.edges[i].to;
  }

  converter.printEquisatisfiableSatFormula();

  return 0;
}
