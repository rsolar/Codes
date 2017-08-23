#include <iostream>

using namespace std;

class Subject {
public:
    virtual void request() = 0;
};

class ConcreteSubject : public Subject {
public:
    void request() {
        cout << "ConcreteSubject::request()" << endl;
    }
};

class Proxy {
public:
    Proxy() : concreteSubject_(new ConcreteSubject()) {}

    ~Proxy() {
        if (concreteSubject_) { delete concreteSubject_; }
    }

    void request() {
        preRequest();
        concreteSubject_->request();
        postRequest();
    }

private:
    void preRequest() {
        cout << "Proxy::preRequest()" << endl;
    }

    void postRequest() {
        cout << "Proxy::postRequest()" << endl;
    }

    ConcreteSubject *concreteSubject_;
};

int main() {
    Proxy *proxy = new Proxy();
    proxy->request();
    delete proxy;
}
