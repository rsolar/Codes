#include "memory_pool.h"

#include <iostream>
#include <ctime>

int main() {
    using std::cin;
    using std::cout;
    using std::endl;

    const int NUMBER_OF_ITEMS = 100;
    const int NUMBER_OF_ITERATIONS = 1000000;

    MemoryPool<char> pool;
    char *variables[NUMBER_OF_ITEMS];

    cout << "Starting to test the pool..." << endl;
    clock_t start = clock();
    for (int i = 0; i < NUMBER_OF_ITERATIONS; i++) {
        for (int j = 0; j < NUMBER_OF_ITEMS; j++) {
            variables[j] = pool.New();
        }
        for (int j = 0; j < NUMBER_OF_ITEMS; j++) {
            pool.Delete(variables[j]);
        }
    }
    clock_t end = clock();
    cout << "Time spent using the pool: " << end - start << " milliseconds" << endl << endl;

    cout << "Starting to test the normal new and delete calls..." << endl;
    start = clock();
    for (int i = 0; i < NUMBER_OF_ITERATIONS; i++) {
        for (int j = 0; j < NUMBER_OF_ITEMS; j++) {
            variables[j] = new char(123);
        }
        for (int j = 0; j < NUMBER_OF_ITEMS; j++) {
            delete variables[j];
        }
    }
    end = clock();
    cout << "Time spent using normal new/delete calls: " << end - start << " milliseconds" << endl << endl;
    cout << "Test finished. Press enter to close." << endl;
    cin.ignore();
}