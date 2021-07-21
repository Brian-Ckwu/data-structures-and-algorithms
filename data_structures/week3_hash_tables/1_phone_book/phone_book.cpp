#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>

using namespace std;

struct Query {
  string type, name;
  int number;
};

vector<Query> read_queries() {
  int n;
  cin >> n;
  vector<Query> queries(n);
  for (int i = 0; i < n; ++i) {
    cin >> queries[i].type;
    if (queries[i].type == "add")
      cin >> queries[i].number >> queries[i].name;
    else
      cin >> queries[i].number;
  }
  return queries;
}

void write_responses(const vector<string>& result) {
  for (size_t i = 0; i < result.size(); ++i)
    std::cout << result[i] << "\n";
}

// starter solution: O(n^2) time complexity / O(n) space complexity
vector<string> process_queries_naive(const vector<Query>& queries) {
  vector<string> result;
  // Keep list of all existing (i.e. not deleted yet) contacts.
  vector<Query> contacts;
  for (size_t i = 0; i < queries.size(); ++i)
    if (queries[i].type == "add") {
      bool was_founded = false;
      // if we already have contact with such number,
      // we should rewrite contact's name
      for (size_t j = 0; j < contacts.size(); ++j)
        if (contacts[j].number == queries[i].number) {
          contacts[j].name = queries[i].name;
          was_founded = true;
          break;
        }
      // otherwise, just add it
      if (!was_founded)
        contacts.push_back(queries[i]);
    } else if (queries[i].type == "del") {
      for (size_t j = 0; j < contacts.size(); ++j)
        if (contacts[j].number == queries[i].number) {
          contacts.erase(contacts.begin() + j);
          break;
        }
    } else {
      string response = "not found";
      for (size_t j = 0; j < contacts.size(); ++j)
        if (contacts[j].number == queries[i].number) {
          response = contacts[j].name;
          break;
        }
      result.push_back(response);
    }
  return result;
}

// my first solution (direct addressing scheme): O(n) time complexity / O(N) space complexity (N is the number of all the possible phone numbewr, i.e. 10^7)
vector<string> process_queries_fast(const vector<Query>& queries) {
  vector<string> result;
  vector<string> contacts(10000000);

  for (const Query& q : queries) {
    if (q.type == "add") {
      contacts[q.number] = q.name;
    } else if (q.type == "del") {
      contacts[q.number] = "";
    } else {
      string res = "not found";
      if (!contacts[q.number].empty()) {
        res = contacts[q.number];
      }
      result.push_back(res);
    }
  }
  return result;
}

// my second solution (using built-in hash map): O(n) time complexity / O(n) space complexity
vector<string> process_queries_hash(const vector<Query>& queries) {
  vector<string> result;
  unordered_map<int, string> phonebook;

  for (const Query& q : queries) {
    if (q.type == "add") {
      phonebook[q.number] = q.name;
    } else if (q.type == "del") {
      phonebook.erase(q.number);
    } else {
      string res = "not found";
      if (phonebook.count(q.number)) {
        res = phonebook[q.number];
      }
      result.push_back(res);
    }
  }
  return result;
}

/*
  my third solution (using my own "hideous" hash map)
*/
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
      ++it;
    }
  }

 private:
  vector<list<HashNode>> map;
  int m;
  int hash(int key, int m) { return key % m; }; // m == cardinality of the hash function
};

// third solution
vector<string> process_queries_myhash(const vector<Query>& queries) {
  vector<string> result;
  HashMap phonebook(queries.size());

  for (const Query& q : queries) {
    if (q.type == "add") {
      HashNode person = {q.number, q.name};
      phonebook.insert(person);
    } else if (q.type == "del") {
      phonebook.erase(q.number);
    } else {
      string res = phonebook.find(q.number);
      result.push_back(res);
    }
  }
  return result;
}

int main() {
  write_responses(process_queries_myhash(read_queries()));
  return 0;
}
