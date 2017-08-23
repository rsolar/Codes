#include <iostream>

using namespace std;

class Target {
public:
    virtual void request() { cout << "Target::request()" << endl; }
};

class Adaptee {
public:
    void specificRequest() { cout << "Adaptee::specificRequest()" << endl; }
};

class Adapter : public Target {
public:
    Adapter() : adaptee_(new Adaptee()) {}

    ~Adapter() { delete adaptee_; }

    void request() {
        adaptee_->specificRequest();
    }

private:
    Adaptee *adaptee_;
};

int main() {
    Target *target = new Adapter();
    target->request();
    delete target;
}
