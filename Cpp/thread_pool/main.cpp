#include "thread_pool.h"

#include <future>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    const int NUMBER_OF_THREADS = 4;
    const int NUMBER_OF_TASKS = 10;

    ThreadPool pool(NUMBER_OF_THREADS);
    vector<std::future<int>> results;

    cout << "Starting to test the pool..." << endl;
    for (int i = 0; i < NUMBER_OF_TASKS; i++) {
        results.emplace_back(
                pool.Enqueue([i] {
                    //cout << "Thread " << i << " starts" << endl;
                    printf("Thread %d starts\n", i);
                    this_thread::sleep_for(chrono::seconds(1));
                    //cout << "Thread " << i << " finishes" << endl;
                    printf("Thread %d finishes\n", i);
                    return i;
                })
        );
    }

    for (auto &&result : results) {
        //cout << "Get result " << result.get() << endl;
        printf("Get result %d\n", result.get());
    }
    cout << endl;

    cout << "Test finished. Press enter to close." << endl;
    cin.ignore();
}
