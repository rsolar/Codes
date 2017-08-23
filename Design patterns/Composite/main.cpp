#include <iostream>
#include <unordered_set>

using namespace std;

class Component {
public:
    virtual void operation() = 0;
};

class ConcreteComponent : public Component {
public:
    ConcreteComponent(int id) : id_(id) {}

    void operation() {
        cout << "ConcreteComponent[" << id_ << "]::operation()" << endl;
    }

private:
    int id_;
};

class Composite : public Component {
public:
    void add(Component *component) {
        components_.insert(component);
    }

    void remove(Component *component) {
        components_.erase(component);
    }

    void operation() {
        for (auto &component : components_) {
            component->operation();
        }
    }

private:
    unordered_multiset<Component *> components_;
};

int main() {
    Component *component1 = new ConcreteComponent(1);
    Component *component2 = new ConcreteComponent(2);
    Component *component3 = new ConcreteComponent(3);
    Composite *composite = new Composite();

    composite->add(component1);
    composite->add(component2);
    composite->add(component3);
    composite->operation();

    delete composite;
    delete component1;
    delete component2;
    delete component3;
}
