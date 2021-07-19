#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Thread {
  int index;
  long long available_time;
};

class CompareClass {
 public:
  bool operator()(const Thread& a, const Thread& b) {
    if (a.available_time > b.available_time) {
      return true;
    } else if (a.available_time == b.available_time) {
      return a.index > b.index;
    } else {
      return false;
    }
  }
};

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m; // num_workers_ == n
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  // Time complexity: O(nm)
  void AssignJobsNaive() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }
  }

  // Time complexity: O(mlogn)
  void AssignJobsFast() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    // Priority queue for storing Thread(index, available_time) pairs, initialized to (i, 0) for i = 0 to n - 1
    priority_queue<Thread, vector<Thread>, CompareClass> threads; // Compare function: smaller available time, if the same then smaller thread index
    for (int i = 0; i < num_workers_; ++i) {
      Thread th = {i, 0};
      threads.push(th);
    }
    // process jobs
    for (int i = 0; i < jobs_.size(); ++i) {
      Thread th = threads.top(); threads.pop(); // O(logn)
      int index = th.index;
      long long start_time = th.available_time;
      int duration = jobs_[i];
      assigned_workers_[i] = index;
      start_times_[i] = start_time;
      Thread new_th = {index, start_time + duration};
      threads.push(new_th); // O(logn)
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobsFast();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
