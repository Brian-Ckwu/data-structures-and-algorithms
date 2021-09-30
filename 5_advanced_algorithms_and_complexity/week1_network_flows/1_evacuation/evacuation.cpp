#include <bits/stdc++.h>

using namespace std;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
 public:
  struct Edge {
    int from, to, capacity, flow;
  };

 private:
  /* List of all - forward and backward - edges */
  vector<Edge> edges;

  /* These adjacency lists store only indices of edges in the edges list */
  vector<vector<size_t>> graph;

 public:
  explicit FlowGraph(size_t n): graph(n) {}

  void add_edge(int from, int to, int capacity) {
    /* Note that we first append a forward edge and then a backward edge,
     * so all forward edges are stored at even indices (starting from 0),
     * whereas backward edges are stored at odd indices in the list edges */
    Edge forward_edge = {from, to, capacity, capacity};
    Edge backward_edge = {to, from, 0, 0};
    graph[from].push_back(edges.size());
    edges.push_back(forward_edge);
    graph[to].push_back(edges.size());
    edges.push_back(backward_edge);
  }

  size_t size() const {
    return graph.size();
  }

  size_t edges_size() const {
    return edges.size();
  }

  const vector<size_t>& get_ids(int from) const {
    return graph[from];
  }

  const Edge& get_edge(size_t id) const {
    return edges[id];
  }

  void add_flow(size_t id, int flow) {
    /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
     * due to the described above scheme. On the other hand, when we have to get a "backward"
     * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
     * should be taken.
     *
     * It turns out that id ^ 1 works for both cases. Think this through! */
    edges[id].flow += flow;
    edges[id ^ 1].flow -= flow;
  }
};

FlowGraph read_data() {
  int vertex_count, edge_count;
  std::cin >> vertex_count >> edge_count;
  FlowGraph graph(vertex_count);
  for (int i = 0; i < edge_count; ++i) {
    int u, v, capacity;
    std::cin >> u >> v >> capacity;
    graph.add_edge(u - 1, v - 1, capacity);
  }
  return graph;
}

vector<size_t> reconstruct_path(int uid, const vector<size_t>& prev) {
  vector<size_t> path;
  while (uid != -1) {
    path.push_back(uid);
    uid = prev[uid];
  }
  return path;
}

vector<size_t> BFS(FlowGraph& graph, int from, int to) {
  vector<size_t> path;
  vector<size_t> prev(graph.edges_size(), -1);
  vector<bool> visited(graph.size(), false);
  queue<int> q;
  q.push(-1);
  while (!q.empty()) {
    int uid = q.front(); q.pop();
    int u = (uid == -1) ? 0 : graph.get_edge(uid).to;
    if (!visited[u]) {
      visited[u] = true;
      if (u == to) {
        path = reconstruct_path(uid, prev);
        break;
      }
      const vector<size_t>& vids = graph.get_ids(u);
      for (size_t vid : vids) {
        if (graph.get_edge(vid).flow > 0) {
          q.push(vid);
          prev[vid] = uid;
        }
      }
    }
  }
  return path;
}

int find_min_flow(FlowGraph& graph, const vector<size_t>& path) {
  int min_flow = INT_MAX;
  for (size_t id : path) {
    int flow = graph.get_edge(id).flow;
    if (flow < min_flow) {
      min_flow = flow;
    }
  }
  return min_flow;
}

void add_flows(FlowGraph& graph, const vector<size_t>& path, int flow) {
  for (size_t id : path) {
    graph.add_flow(id, -flow);
  }
}

// Edmonds-Karp Algorithm
int max_flow(FlowGraph& graph, int from, int to) {
  int flow = 0;
  while (true) {
    vector<size_t> path = BFS(graph, from, to);
    if (path.empty()) {
      break;
    }
    int min_flow = find_min_flow(graph, path);
    flow += min_flow;
    add_flows(graph, path, min_flow);
  }
  return flow;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  FlowGraph graph = read_data(); // initial network G

  std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
  return 0;
}
