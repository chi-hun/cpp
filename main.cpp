// 15-2
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <future>
#include <functional>
#include <condition_variable>
#include <thread>
#include <mutex>



using namespace std;

namespace ThreadPool {
class ThreadPool {
    private:
        size_t num_threads_;
        vector<thread> worker_threads_;
        queue<function<void()>> jobs_;
        condition_variable cv_job_q_;
        mutex m_job_q_;
        bool stop_all;
        void Worker_Thread();

    public:
        ThreadPool(size_t num_threads);
        ~ThreadPool();
        void EnqueueJob(function<void()> job);
};

ThreadPool::ThreadPool(size_t num_threads) : num_threads_(num_threads), stop_all(false) {
    worker_threads_.reserve(num_threads);
    for (size_t i=0; i < num_threads; ++i) {
        worker_threads_.emplace_back([this]() {this->Worker_Thread();});
    }
}

ThreadPool::~ThreadPool() {
    stop_all = true;
    cv_job_q_.notify_all();
    for (thread& t : worker_threads_) {
        t.join();
    }
}

void ThreadPool::Worker_Thread() {
    while (true) {
        unique_lock<mutex> lock(m_job_q_);
        cv_job_q_.wait(lock, [this]() {return !jobs_.empty() || stop_all;});
        if (stop_all && jobs_.empty()) {
            return;
        }
        function<void()> job = move(jobs_.front());
        jobs_.pop();
        lock.unlock();
        job();
    }
}

void ThreadPool::EnqueueJob(function<void()> job) {
    if (stop_all) {
        throw runtime_error("ThreadPool 사용중지");
    }
    { lock_guard<mutex> lock(m_job_q_);
        jobs_.push(move(job));
    }
    cv_job_q_.notify_one();
}
}

void work(int t, int id) {
    printf("%d start \n", id);
  std::this_thread::sleep_for(std::chrono::seconds(t));
  printf("%d end after %ds\n", id, t);
}

int main() {
    ThreadPool::ThreadPool pool(3);

    for (int i = 0; i < 10; i++) {
        pool.EnqueueJob([i]() { work(i % 3 + 1, i); });
    }
    return 0;
}
