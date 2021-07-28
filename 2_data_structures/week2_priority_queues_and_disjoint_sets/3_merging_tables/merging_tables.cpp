#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
	int size, parent, rank;
	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector<DisjointSetsElement> sets;

	DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int table) {
		if (table != sets[table].parent) {
			sets[table].parent = getParent(sets[table].parent);
		}
		return sets[table].parent;
	}

	void merge(int destination, int source) {
		int realDestination = getParent(destination);
		int realSource = getParent(source);
		if (realDestination != realSource) {
			DisjointSetsElement& dest = sets[realDestination];
			DisjointSetsElement& source = sets[realSource];
			// use rank heuristic to merge to maintain efficiency of getParent (not necessary to attach real source to real destination)
			if (dest.rank > source.rank) {
				source.parent = dest.parent;
				dest.size += source.size;
			} else {
				dest.parent = source.parent;
				source.size += dest.size;
				if (dest.rank == source.rank) {
					++source.rank;
				}
			}
			// without rank heuristic
			// source.parent = dest.parent;
			// dest.size += source.size;
			max_table_size = max(max_table_size, max(dest.size, source.size));
		}		
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	for (auto& table : tables.sets) {
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
		// change to 0-based index
    --destination;
    --source;
		// merge tables
		tables.merge(destination, source);
	  cout << tables.max_table_size << endl;
	}

	return 0;
}
