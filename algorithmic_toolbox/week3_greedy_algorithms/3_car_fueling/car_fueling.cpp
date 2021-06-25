#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int>& stops) {
    // Variables
    int refill_loc = 0;
    int refills = 0;

    // Push the destination into the stops
    stops.push_back(dist);

    // Main loop
    int i = -1;
    while (dist - refill_loc > tank) {
        // Find the farthest reachable gas station
        while (stops[i + 1] - refill_loc <= tank) {
            ++i;
        }

        // If impossible to refill
        if (i == -1 || stops[i] == refill_loc) {
            return -1;
        }

        // Refill
        refill_loc = stops[i];
        ++refills;
    }

    return refills;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
