#include <iostream>

using namespace std;

class Component {
public:
    virtual void operation() = 0;
};

class ConcreteComponent : public Component {
public:
    void operation() {
        cout << "ConcreteComponent::operation()" << endl;
    }
};

class Decorator : public Component {
public:
    Decorator(Component *comp) : comp_(comp) {}

    virtual ~Decorator() {}

    virtual void operation() = 0;

protected:
    Component *comp_;
};

class ConcreteDecorator : public Decorator {
public:
    ConcreteDecorator() : Decorator(new ConcreteComponent) {}

    ~ConcreteDecorator() {
        delete comp_;
    }

    void operation() {
        comp_->operation();
        addedBehavior();
    }

    void addedBehavior() {
        cout << "ConcreteDecorator::addedBehavior()" << endl;
    }
};

int main() {
    Decorator *decorator = new ConcreteDecorator();
    decorator->operation();
    delete decorator;
}
