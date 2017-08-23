#include <iostream>

using namespace std;

class Api {
public:
    Api() { cout << "Api::Api()" << endl; }

    virtual ~Api() { cout << "Api::~Api()" << endl; }

    virtual void Operation(const string &op) const = 0;
};

class ImplA : public Api {
public:
    ImplA() { cout << "ImplA::ImplA()" << endl; }

    ~ImplA() { cout << "ImplA::~ImplA()" << endl; }

    void Operation(const string &op) const { cout << "ImplA::Operation(): " << op << endl; }
};

class ImplB : public Api {
public:
    ImplB() { cout << "ImplB::ImplB()" << endl; }

    ~ImplB() { cout << "ImplB::~ImplB()" << endl; }

    void Operation(const string &op) const { cout << "ImplB::Operation(): " << op << endl; }
};

class Factory {
public:
    static Api *CreateApi(const string &name) {
        if ("A" == name) { return new ImplA(); }
        else if ("B" == name) { return new ImplB(); }
        return nullptr;
    }
};

int main() {
    Api *implA = Factory::CreateApi("A");
    Api *implB = Factory::CreateApi("B");

    implA->Operation("test");
    implB->Operation("test");

    delete implA;
    delete implB;
}
