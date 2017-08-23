#include <iostream>

using namespace std;

class Implementor {
public:
    virtual void operation() = 0;
};

class ConcreteImplementA : public Implementor {
public:
    void operation() {
        cout << "ConcreteImplementA::operation()" << endl;
    }
};

class ConcreteImplementB : public Implementor {
public:
    void operation() {
        cout << "ConcreteImplementB::operation()" << endl;
    }
};

class Abstraction {
public:
    virtual void operation() = 0;
};

class RefinedAbstraction : public Abstraction {
public:
    RefinedAbstraction(Implementor *impl) : impl_(impl) {}

    ~RefinedAbstraction() {}

    void operation() {
        impl_->operation();
    }

private:
    Implementor *impl_;
};

int main() {
    ConcreteImplementA *concreteImplementA = new ConcreteImplementA();
    Abstraction *abstractionA = new RefinedAbstraction(concreteImplementA);
    abstractionA->operation();

    ConcreteImplementB *concreteImplementB = new ConcreteImplementB();
    Abstraction *abstractionB = new RefinedAbstraction(concreteImplementB);
    abstractionB->operation();

    delete abstractionA;
    delete concreteImplementA;
    delete abstractionB;
    delete concreteImplementB;
}
