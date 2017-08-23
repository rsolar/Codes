#include <iostream>
#include <pthread.h>

using namespace std;

// Eager initialization
class Singleton {
public:
    static Singleton *getInstance() {
        return instance_;
    }

protected:
    Singleton() {}

private:
    static Singleton *instance_;
};

Singleton *Singleton::instance_ = new Singleton();

// Lazy initialization w/o thread-safe
/*
class Singleton {
public:
    static Singleton *getInstance() {
        if (instance_ == NULL) {
            instance_ = new Singleton();
        }
        return instance_;
    }

protected:
    Singleton() {}

private:
    static Singleton *instance_;
};

Singleton *Singleton::instance_ = NULL;
*/

// Lazy initialization w/ thread-safe in C++11
/*
class Singleton {
public:
    static Singleton *getInstance() {
        static Singleton instance;
        return &instance;
    }

protected:
    Singleton() {}
};
*/

// Lazy initialization w/ thread-safe using pthread
/*
class Singleton {
public:
    static Singleton *getInstance() {
        if (instance_ == NULL) {
            pthread_mutex_lock(&mutex_);
            if (instance_ == NULL) {
                instance_ = new Singleton();
            }
            pthread_mutex_unlock(&mutex_);
        }
        return instance_;
    }

protected:
    Singleton() {}

private:
    static Singleton *instance_;
    static pthread_mutex_t mutex_;
};

Singleton *Singleton::instance_ = NULL;
pthread_mutex_t Singleton::mutex_;
*/

int main() {
    Singleton *instance = Singleton::getInstance();
    
    delete instance;
}
