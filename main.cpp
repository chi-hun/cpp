// 15-2
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <chrono>
#include <condition_variable>

using namespace std;

void producer(queue<string>* downloaded_pages, mutex* m, int index, condition_variable* cv) {
    for (int i=0; i < 5; i++) {
        this_thread::sleep_for(chrono::milliseconds(100*index));
        string content = "웹사이트 : " + to_string(i) + "from thread (" + to_string(index) + ")";

        m->lock();
        downloaded_pages->push(content);
        m->unlock();

        cv->notify_one();
    }
}

void consumer(queue<string>* downloaded_pages, mutex* m, int* num_processed, condition_variable* cv) {
    while (*num_processed < 25) {
        unique_lock<mutex> lock(*m);

        cv->wait(
            lock, [&] {return !downloaded_pages->empty() || *num_processed == 25;}
        );

        if (*num_processed == 25) {
            lock.unlock();
            return;
        }

        string content = downloaded_pages->front();
        downloaded_pages->pop();
        (*num_processed)++;

       lock.unlock();

        cout << content << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}


int main() {
    queue<string> downloaded_pages;
    mutex m;
    int num_processed = 0;
    vector<thread> threads_p;
    vector<thread> threads_c;
    condition_variable cv;

    for (int i=0; i < 5; i++) {
        threads_p.push_back(thread(producer, &downloaded_pages, &m, i, &cv));
    }

    for (int i=0; i < 3; i++) {
        threads_c.push_back(thread(consumer, &downloaded_pages, &m, &num_processed, &cv));
    }

    for (int i=0; i < 5; i++) {
        threads_p[i].join();
    }

    cv.notify_all();

    for (int i=0; i < 3; i++) {
        threads_c[i].join();
    }

    return 0;
}
