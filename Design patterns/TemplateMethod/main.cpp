#include <iostream>

using namespace std;

class Operation {
public:
    void execute() {
        before();
        operate1();
        middle();
        operate2();
        after();
    }

    void before() {
        cout << "Base::before()" << endl;
    }

    void middle() {
        cout << "Base::middle()" << endl;
    }

    void after() {
        cout << "Base::after()" << endl;
    }

    virtual void operate1() = 0;

    virtual void operate2() = 0;
};

class ConcreteOperationA : public Operation {
public:
    void operate1() {
        cout << "ConcreteOperationA::operation1()" << endl;
    }

    void operate2() {
        cout << "ConcreteOperationA::operation2()" << endl;
    }
};

class ConcreteOperationB : public Operation {
public:
    void operate1() {
        cout << "ConcreteOperationB::operation1()" << endl;
    }

    void operate2() {
        cout << "ConcreteOperationB::operation2()" << endl;
    }
};

int main() {
    Operation *operationA = new ConcreteOperationA();
    Operation *operationB = new ConcreteOperationB();

    operationA->execute();
    operationB->execute();

    delete operationA;
    delete operationB;
}
