#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;

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

  // Time complexity:
  void AssignJobsFast() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    // Priority queue for storing (thread, available_time) pairs, initialized to (i, 0) for i = 0 to n - 1
    // Compare function: smaller available time, if the same then smaller thread index

    // for work = 0 to m - 1:
      // choose the thread with the highest priority (top element); pop the top element
      // thread = top_element.first
      // start_time = top_element.second
      // duration = duration[work]
      // assigned_workers_[work] = thread
      // start_times_[work] = start_time
      // available_time
      // push the new (thread, available_time) pair
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
