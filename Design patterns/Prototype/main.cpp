#include <iostream>

using namespace std;

class Prototype {
public:
    virtual Prototype *clone() = 0;
};

class ConcretePrototype : public Prototype {
public:
    ConcretePrototype() {}

    ConcretePrototype(const ConcretePrototype &source) {
        cout << "ConcretePrototype::ConcretePrototype(const ConcretePrototype &)" << endl;
    }

    Prototype *clone() {
        return new ConcretePrototype(*this);
    }
};

int main() {
    Prototype *prototype = new ConcretePrototype();
    Prototype *p1 = prototype->clone();
    delete prototype;
    delete p1;
}
