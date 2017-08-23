#include <iostream>

using namespace std;

class SubSystemA {
public:
    void operation() {
        cout << "SubSystemA::operation()" << endl;
    }
};

class SubSystemB {
public:
    void operation() {
        cout << "SubSystemB::operation()" << endl;
    }
};

class Facade {
public:
    Facade() : subSystemA_(new SubSystemA()), subSystemB_(new SubSystemB()) {}

    ~Facade() {
        if (subSystemA_) { delete subSystemA_; }
        if (subSystemB_) { delete subSystemB_; }
    }

    void wrappedOperation() {
        subSystemA_->operation();
        subSystemB_->operation();
    }

private:
    SubSystemA *subSystemA_;
    SubSystemB *subSystemB_;
};

int main() {
    Facade *facade = new Facade();
    facade->wrappedOperation();
    delete facade;
}
