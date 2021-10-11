#include <sys/resource.h>
#include <bits/stdc++.h>

using namespace std;

struct Vertex {
  int weight;
  vector<int> children;
};
typedef vector<Vertex> Graph;
typedef vector<int> Sum;

Graph ReadTree() {
  int vertices_count;
  cin >> vertices_count;

  Graph tree(vertices_count);

  for (int i = 0; i < vertices_count; ++i)
    cin >> tree[i].weight;

  for (int i = 1; i < vertices_count; ++i) {
    int from, to, weight;
    cin >> from >> to;
    tree[from - 1].children.push_back(to - 1);
    tree[to - 1].children.push_back(from - 1);
  }

  return tree;
}

void dfs(const Graph& tree, int vertex, int parent, vector<int>& fun_sum) {
  for (int child : tree[vertex].children) {
    if (child != parent) {
      dfs(tree, child, vertex, fun_sum);
    }
  }
  // calculate the maximum sum of fun factors
  int m1 = tree[vertex].weight; // maximum sum of the fun factors including the vertex
  int m0 = 0; // maximum sum of the fun factors excluding the vertex
  for (int child : tree[vertex].children) {
    if (child != parent) {
      m0 += fun_sum[child];
      for (int grandchild : tree[child].children) {
        if (grandchild != vertex) {
          m1 += fun_sum[grandchild];
        }
      }
    }
  }
  // record the maximum sum
  fun_sum[vertex] = max(m0, m1);
}

int MaxWeightIndependentTreeSubset(const Graph& tree) {
  size_t size = tree.size();
  if (size == 0)
    return 0;
  vector<int> fun_sum(size, 0);
  dfs(tree, 0, -1, fun_sum);
  return fun_sum[0];
}

int main() {
  // This code is here to increase the stack size to avoid stack overflow
  // in depth-first search.
  const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
  struct rlimit rl;
  int result;
  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
    if (rl.rlim_cur < kStackSize)
    {
      rl.rlim_cur = kStackSize;
      result = setrlimit(RLIMIT_STACK, &rl);
      if (result != 0)
      {
        fprintf(stderr, "setrlimit returned result = %d\n", result);
      }
    }
  }

  // Here begins the solution
  Graph tree = ReadTree();
  int weight = MaxWeightIndependentTreeSubset(tree);
  cout << weight << endl;
  return 0;
}
