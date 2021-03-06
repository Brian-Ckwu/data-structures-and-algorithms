#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class Node;

class Node {
 public:
  int key;
  Node* parent;
  vector<Node*> children;

  Node() {
    this->parent = NULL;
  }

  void setParent(Node* theParent) {
    parent = theParent;
    parent->children.push_back(this);
  }
};

// What is the time complexity?
int get_tree_height_naive(vector<Node>& nodes) {
  // Replace this code with a faster implementation
  int max_height = 0;
  for (int leaf_index = 0; leaf_index < nodes.size(); leaf_index++) {
    int height = 0;
    for (Node* v = &nodes[leaf_index]; v != NULL; v = v->parent)
      height++;
    max_height = max(max_height, height);
  }
  
  return max_height;
}

int get_node_height_recur(Node* node) {
  if (node->children.empty()) {
    return 1;
  }

  int max_height = 0;
  for (Node*& child_node : node->children) {
    int height = 1 + get_node_height_recur(child_node);
    max_height = max(max_height, height);
  }

  return max_height;
}

// DFS approach: What is the time complexity?
int get_tree_height_recur(vector<Node>& nodes) {
  for (Node& node : nodes) {
    if (!node.parent) {
      Node& root = node;
      return get_node_height_recur(&root);
    }
  }
  throw "There is no root.";
}

// BFS: What is the time complexity?
int get_tree_height_bfs(vector<Node>& nodes) {
  // Find the root
  Node* root = nullptr;
  for (Node& node : nodes) {
    if (!node.parent) {
      root = &node;
      break;
    }
  }

  if (root == nullptr) {
    throw "There is no root.";
  }

  // Start traversing the tree from the root
  queue<Node*> node_queue;
  node_queue.push(root);
  int tree_height = 0;

  Node* level_last = node_queue.back();
  while (!node_queue.empty()) {
    Node* node = node_queue.front();
    node_queue.pop();

    if (!(node->children.empty())) {
      for (Node* child_node : node->children) {
        node_queue.push(child_node);
      }
    }

    if (node == level_last) {
      ++tree_height;
      level_last = node_queue.back();
    }
  }

  return tree_height;
}

vector<Node> read_nodes_default() {
  ios_base::sync_with_stdio(0);
  int n;
  cin >> n;

  vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    nodes[child_index].key = child_index;
  }

  return nodes;
}

vector<Node> read_nodes_from_file(ifstream& ist) {
  int n;
  ist >> n;

  vector<Node> nodes(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    ist >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    nodes[child_index].key = child_index;
  }

  return nodes;
}

void stress_test() {
  int kFileNum = 24;
  int kFileLen = 2;

  for (int i = 1; i <= kFileNum; ++i) {
    string file_index = to_string(i);
    string case_file = string(kFileLen - file_index.length(), '0') + file_index;  // pad leading zeros
    string ans_file = case_file + ".a";

    string file_folder = "./tests/";
    ifstream ist;
    // Open case file
    ist.open(file_folder + case_file);
    if (!ist) { // check opened
      throw "ERROR";
    }

    // Output case
    cout << "Test case #" << file_index << ":" << endl;

    vector<Node> nodes = read_nodes_from_file(ist);
    // int tree_height_naive = get_tree_height_naive(nodes);
    int tree_height_sol = get_tree_height_bfs(nodes);
    // Close case file
    ist.close();

    // Open ans file
    ist.open(file_folder + ans_file);
    if (!ist) {
      throw "ERROR";
    }

    // Output ans
    int tree_height_ans = -1;
    ist >> tree_height_ans;
    if (tree_height_sol == tree_height_ans) {
      cout << "Got tree height right: " << tree_height_sol << endl;
    } else {
      cout << "Got tree height wrong: " << endl;
      cout << "Answer: " << tree_height_ans << endl;
      cout << "Got: " << tree_height_sol << endl;
    }
    cout << endl;

    // Close ans file
    ist.close();
  }  
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
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
        cerr << "setrlimit returned result = " << result << endl;
      }
    }
  }

#endif
  stress_test();
  // vector<Node> nodes = read_nodes_default();
  // int tree_height = get_tree_height_bfs(nodes);
  // cout << tree_height;
  return 0;
}
