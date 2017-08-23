#include <iostream>

using namespace std;

class Api {
public:
    virtual void Operation(const string &op) const = 0;
};

class ImplA : public Api {
public:
    void Operation(const string &op) const { cout << "ImplA::Operation(): " << op << endl; }
};

class ImplB : public Api {
public:
    void Operation(const string &op) const { cout << "ImplB::Operation(): " << op << endl; }
};

class Factory {
public:
    virtual Api *CreateApi() = 0;
};

class ImplAFactory: public Factory {
public:
    Api *CreateApi() { return new ImplA(); }
};

class ImplBFactory: public Factory {
public:
    Api *CreateApi() { return new ImplB(); }
};

int main() {
    ImplAFactory *implAFactory = new ImplAFactory();
    ImplBFactory *implBFactory = new ImplBFactory();
    Api *implA = implAFactory->CreateApi();
    Api *implB = implBFactory->CreateApi();

    implA->Operation("testA");
    implB->Operation("testB");

    delete implA;
    delete implB;
    delete implAFactory;
    delete implBFactory;
}
