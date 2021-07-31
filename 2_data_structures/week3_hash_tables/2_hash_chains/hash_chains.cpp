#include <bits/stdc++.h>

using namespace std;

struct Query {
  string type, s;
  size_t ind;
};

class QueryProcessor {
  int bucket_count;
  // store the strings in the hash table
  vector<list<string>> table;
  size_t hash_func(const string& s) const {
    static const size_t multiplier = 263;
    static const size_t prime = 1000000007;
    unsigned long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
      hash = (hash * multiplier + s[i]) % prime;
    return hash % bucket_count;
  }

public:
  explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
    table.resize(bucket_count);
  }

  Query readQuery() const {
    Query query;
    cin >> query.type;
    if (query.type != "check")
      cin >> query.s;
    else
      cin >> query.ind;
    return query;
  }

  void writeSearchResult(bool was_found) const {
    std::cout << (was_found ? "yes\n" : "no\n");
  }

  void processQuery(const Query& query) {
    if (query.type == "check") {
      // use reverse order, because we append strings to the end
      list<string>& chain = table[query.ind];
      for (string& s : chain) {
        std::cout << s << " ";
      }
      std::cout << "\n";
    } else {
      size_t hash_value = hash_func(query.s);
      list<string>& chain = table[hash_value];
      list<string>::iterator it = find(chain.begin(), chain.end(), query.s);
      if (query.type == "add") {
        if (it == chain.end()) // if the string is not found -> append to chain
          chain.push_front(query.s);
      } else if (query.type == "del") {
        if (it != chain.end()) // if the string is found -> erase from chain
          chain.erase(it);
      } else if (query.type == "find") {
        writeSearchResult(it != chain.end());
      } else {
        throw "ERROR";
      }
    }
  }

  void processQueries() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
      processQuery(readQuery());
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  int bucket_count;
  cin >> bucket_count;
  QueryProcessor proc(bucket_count);
  proc.processQueries();
  return 0;
}
