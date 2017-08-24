#include <iostream>

using namespace std;

class Element;
class ConcreteElementA;
class ConcreteElementB;

class Visitor {
public:
    virtual void visit(ConcreteElementA *) = 0;
    virtual void visit(ConcreteElementB *) = 0;
};

class ConcreteVisitor : public Visitor {
public:
    void visit(ConcreteElementA *element) {
        cout << "ConcreteVisitor is visiting ConcreteElementA" << endl;
    }

    void visit(ConcreteElementB *element) {
        cout << "ConcreteVisitor is visiting ConcreteElementB" << endl;
    }
};

class Element {
public:
    virtual void accept(Visitor *visitor) = 0;
};

class ConcreteElementA : public Element {
public:
    void accept(Visitor *visitor) {
        cout << "ConcreteElementA is being visited" << endl;
        visitor->visit(this);
    }
};

class ConcreteElementB : public Element {
public:
    void accept(Visitor *visitor) {
        cout << "ConcreteElementB is being visited" << endl;
        visitor->visit(this);
    }
};

int main() {
    Element *elementA = new ConcreteElementA();
    Element *elementB = new ConcreteElementB();
    Visitor *visitor = new ConcreteVisitor();

    elementA->accept(visitor);
    elementB->accept(visitor);

    delete visitor;
    delete elementA;
    delete elementB;
}
