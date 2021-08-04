#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Data {
  string pattern, text;
};

Data read_input() {
  Data data;
  std::cin >> data.pattern >> data.text;
  return data;
}

void print_occurrences(const vector<int>& output) {
  for (size_t i = 0; i < output.size(); ++i)
    std::cout << output[i] << " ";
  std::cout << "\n";
}

ll polyhash(const string& text, int start, int end, ll prime, ll x) {
  ll hash = 0;
  for (int i = end; i >= start; --i) {
    hash = ((ll) text[i] + hash * x) % prime;
  }
  // cout << hash << endl;
  return hash;
}

vector<ll> precompute_hashes(const string& text, int pattern_len, ll prime, ll x) {
  size_t n = text.size() - pattern_len;
  vector<ll> hashes(n + 1);
  hashes[n] = polyhash(text, n, n + pattern_len - 1, prime, x);
  // compute x ^ pattern_len
  ll y = 1;
  for (int i = 0; i < pattern_len; ++i) {
    y = (y * x) % prime;
  }
  for (int i = n - 1; i >= 0; --i) {
    hashes[i] = ((((ll) text[i] + x * hashes[i + 1] - y * (ll) text[i + pattern_len]) % prime) + prime) % prime;
  }
  return hashes;
}

bool are_equal(const string& pattern, const string& text, int start) {
  for (int i = 0; i < pattern.size(); ++i) {
    if (pattern[i] != text[start + i])
      return false;
  }
  return true;
}

vector<int> get_occurrences(const Data& input) {
  const string& s = input.pattern, t = input.text;
  vector<int> ans;
  ll prime = 340029919604281;
  int x = rand() % 100 + 1;
  // compute p_hash & precompute t_hashes
  ll p_hash = polyhash(s, 0, s.size() - 1, prime, x);
  vector<ll> t_hashes = precompute_hashes(t, s.size(), prime, x);
  // search pattern
  for (int i = 0; i <= t.size() - s.size(); ++i) {
    if (p_hash != t_hashes[i])
      continue;
    if (are_equal(s, t, i))
      ans.push_back(i);
  }
  return ans;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  print_occurrences(get_occurrences(read_input()));
  return 0;
}
