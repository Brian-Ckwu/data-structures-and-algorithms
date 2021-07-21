/*
  A very simple implementation of a hash map for integers to string
*/

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class HashNode {
 public:
  int key;
  string value;
};

class HashMap {
 public:
  HashMap(int n)
    : m{2 * n} {
      map.resize(2 * n);
    }
  
  void insert(HashNode& node) {
    int index = hash(node.key, m);
    list<HashNode>& chain = map[index];
    for (HashNode& elem : chain) {
      if (elem.key == node.key) {
        elem.value = node.value;
        return;
      }
    }
    chain.push_back(node);
  }

  string find(int key) {
    int index = hash(key, m);
    list<HashNode>& chain = map[index];
    for (HashNode& elem : chain) {
      if (elem.key == key) {
        return elem.value;
      }
    }
    return "not found";
  }

  void erase(int key) {
    int index = hash(key, m);
    list<HashNode>& chain = map[index];
    list<HashNode>::iterator it = chain.begin();
    while (it != chain.end()) {
      if (it->key == key) {
        chain.erase(it);
        break;
      }
    }
  }

 private:
  vector<list<HashNode>> map;
  int m;
  int hash(int key, int m) { return key % m; }; // m == cardinality of the hash function
};

int main() {
  vector<HashNode> nodes = {
    {3, "Apple"},
    {8, "Banana"},
    {7, "Cider"},
    {3, "Hehe"},
    {5, "Diana"},
    {1, "Eat"}
  };

  HashMap hash_map(nodes.size());

  for (HashNode& node: nodes) {
    hash_map.insert(node);
  }

  cout << hash_map.find(3) << endl;
  cout << hash_map.find(8) << endl;
  cout << hash_map.find(7) << endl;
  cout << hash_map.find(5) << endl;
  cout << hash_map.find(1) << endl;

  hash_map.erase(5);
  hash_map.erase(7);
  HashNode node = {1, "Changed"};
  hash_map.insert(node);

  cout << hash_map.find(3) << endl;
  cout << hash_map.find(8) << endl;
  cout << hash_map.find(7) << endl;
  cout << hash_map.find(5) << endl;
  cout << hash_map.find(1) << endl;

  return 0;
}