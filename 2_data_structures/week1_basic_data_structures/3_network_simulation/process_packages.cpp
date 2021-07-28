#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

struct Request {
  Request(int arrival_time, int process_time):
    arrival_time(arrival_time),
    process_time(process_time)
  {}

  int arrival_time;
  int process_time;
};

struct Response {
  Response(bool dropped, int start_time):
    dropped(dropped),
    start_time(start_time)
  {}

  bool dropped;
  int start_time;
};

class Buffer {
 public:
  Buffer(int size):
    size_(size),
    finish_time_()
  {}

  Response Process(const Request& request) {
    // main implementation code
    // check if we can pop the previous packets
    while (!finish_time_.empty()) {
      if (finish_time_.front() <= request.arrival_time) {
        finish_time_.pop();
      } else {
        break;
      }
    }

    // see if we can push the packet
    // if not, return -1
    if (finish_time_.size() == size_) {
      return Response(true, -1);
    }
    // else, then it is guaranteed to be processed in the end (so return the start processing time)
    int start_time = (finish_time_.empty()) ? request.arrival_time : max(finish_time_.back(), request.arrival_time);
    int finish_time = start_time + request.process_time;
    finish_time_.push(finish_time);

    return Response(false, start_time);
  }
 private:
  int size_;
  queue <int> finish_time_;
};

vector <Request> ReadRequests() {
  vector <Request> requests;
  int count;
  cin >> count;
  for (int i = 0; i < count; ++i) {
    int arrival_time, process_time;
    cin >> arrival_time >> process_time;
    requests.push_back(Request(arrival_time, process_time));
  }
  return requests;
}

vector <Response> ProcessRequests(const vector <Request>& requests, Buffer* buffer) {
  vector <Response> responses;
  for (int i = 0; i < requests.size(); ++i)
    responses.push_back(buffer->Process(requests[i]));
  return responses;
}

void PrintResponses(const vector <Response> &responses) {
  for (int i = 0; i < responses.size(); ++i)
    cout << (responses[i].dropped ? -1 : responses[i].start_time) << endl;
}

vector <Request> ReadRequestsFromFile(ifstream& ist) {
  vector <Request> requests;
  int count;
  ist >> count;
  for (int i = 0; i < count; ++i) {
    int arrival_time, process_time;
    ist >> arrival_time >> process_time;
    requests.push_back(Request(arrival_time, process_time));
  }
  return requests;
}

void stress_test() {
  const int case_num = 22;
  const int file_len = 2;
  string file_dir = "./tests/";

  // loop from test file 01 to 22
  for (int i = 1; i <= case_num; ++i) {
    string fnum_str = to_string(i);
    string case_file = string(file_len - fnum_str.size(), '0') + fnum_str;
    string ans_file = case_file + ".a";

    // open the case file
    ifstream ist;
    ist.open(file_dir + case_file);

    if (!ist) {
      throw "ERROR";
    }
    // read input
    int size;
    ist >> size;
    vector <Request> requests = ReadRequestsFromFile(ist);

    // get the result
    Buffer buffer(size);
    vector <Response> responses = ProcessRequests(requests, &buffer);

    // close the case file
    ist.close();

    // open the ans file
    ist.open(file_dir + ans_file);

    if (!ist) {
      throw "ERROR";
    }

    // read answers
    vector<int> answers;
    int answer;
    while (ist >> answer) {
      answers.push_back(answer);
    }

    // compare the result with the ans
    cout << "Test case #" << i << ":" << endl;

    assert(answers.size() == responses.size());

    for (int i = 0; i < answers.size(); ++i) {
      int ans = answers[i];
      int res = responses[i].dropped ? -1 : responses[i].start_time;
      assert(ans == res);
    }

    cout << "The result is correct." << endl << endl;
  }
}

int main() {
  // stress_test();

  int size;
  cin >> size;
  vector <Request> requests = ReadRequests();

  Buffer buffer(size);
  vector <Response> responses = ProcessRequests(requests, &buffer);

  PrintResponses(responses);

  return 0;
}
