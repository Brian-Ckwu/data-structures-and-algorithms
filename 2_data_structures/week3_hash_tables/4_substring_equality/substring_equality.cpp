#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void gen_test_cases(int str_len) {
	for (int i = 0; i < str_len; ++i) {
		for (int j = 0; j < str_len; ++j) {
			for (int k = 1; k <= str_len - max(i, j); ++k) {
				cout << i << " " << j << " " << k << endl;
			}
		}
	}
}

class Solver {
 public:	
	Solver(string s) : s(s) {	
		// initialization
		p = 340029919604281;
		x = 1;
		// precalculation
		pre_hashes = hash_prefixes(s);
	}

	bool are_equal(int a, int b, int l) {
		for (int i = 0; i < l; ++i) {
			if (s[a + i] != s[b + i])
				return false;
		}
		return true;
	}

	bool ask(int a, int b, int l) {
		// check if the hash values are equal
		ll a_hash = get_hash(a, a + l - 1);
		ll b_hash = get_hash(b, b + l - 1);
		if (a_hash != b_hash)
			return false;
		return are_equal(a, b, l);
	}

 private:
  string s;
	ll p;
	ll x;
	vector<ll> pre_hashes;

	vector<ll> hash_prefixes(const string& s) {
		vector<ll> hashes(s.size());
		hashes[0] = s[0];
		for (int i = 1; i < s.size(); ++i) {
			hashes[i] = (hashes[i - 1] * x + s[i]) % p;
		}
		return hashes;
	}

	ll get_hash(int start, int end) {
		ll left_hash = (start > 0) ? pre_hashes[start - 1] : 0;
		ll right_hash = pre_hashes[end];
		ll y = 1;
		for (int i = 0; i < end - start + 1; ++i) {
			y = (y * x) % p;
		}
		ll hash = ((right_hash - left_hash * y) % p + p) % p;
		return hash;
	}
};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
