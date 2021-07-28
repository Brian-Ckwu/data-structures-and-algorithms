#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int search_start(vector<int>& a, int point) {
  int low = 0, high = a.size() - 1;
  int mid;
  while (low <= high) {
    mid = (low + high) / 2;
    if (point >= a[mid]) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return ((low > mid) ? mid + 1 : mid);
}

int search_end(vector<int>& a, int point) {
  int low = 0, high = a.size() - 1;
  int mid;
  while (low <= high) {
    mid = (low + high) / 2;
    if (point <= a[mid]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return ((high < mid) ? mid : mid + 1);
}

// O(nlogn) + O(nlogn) + 2n*O(logn) = O(nlogn)
vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  sort(starts.begin(), starts.end());
  sort(ends.begin(), ends.end());
  for (int i = 0; i < points.size(); ++i) { // search the position of "point" in sorted starts and ends
    int start_pos = search_start(starts, points[i]);
    int end_pos = search_end(ends, points[i]);
    cnt[i] = start_pos - end_pos;
  }
  return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
