#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	bool patternEnd;

	Node ()
	{
		fill (next, next + Letters, NA);
		patternEnd = false;
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

vector<Node> build_trie(const vector<string>& patterns) {
	vector<Node> trie;
	trie.resize(1);
	for (const string& pattern : patterns) {
		int node = 0;
		for (char ch : pattern) {
			int index = letterToIndex(ch);
			if (trie[node].next[index] == NA) {
				int new_node = trie.size();
				trie[node].next[index] = new_node;
				trie.push_back(Node());
				node = new_node;
			} else {
				node = trie[node].next[index];
			}
		}
		trie[node].patternEnd = true;
	}
	return trie;
}

vector <int> solve (string text, int n, vector<string> patterns)
{
	// build trie
	vector<Node> trie = build_trie(patterns);
	// traverse text using the trie
	vector<int> result;
	for (int i = 0; i < text.size(); ++i) {
		Node* node = &trie[0];
		int j = i;
		while ((j < text.size()) && node->next[letterToIndex(text[j])] != NA) {
			node = &trie[node->next[letterToIndex(text[j])]];
			if (node->patternEnd) {
				result.push_back(i);
				break;
			}
			++j;
		}
	}
	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
