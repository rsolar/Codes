#include <iostream>

using namespace std;

class AbstractProductA {
};

class AbstractProductB {
};

class ConcreteProductA1 : public AbstractProductA {
};

class ConcreteProductA2 : public AbstractProductA {
};

class ConcreteProductB1 : public AbstractProductB {
};

class ConcreteProductB2 : public AbstractProductB {
};

class AbstractFactory {
public:
    virtual AbstractProductA *CreateProductA() = 0;

    virtual AbstractProductB *CreateProductB() = 0;
};

class ConcreteFactory1 : public AbstractFactory {
public:
    virtual AbstractProductA *CreateProductA() {
        return new ConcreteProductA1();
    }

    virtual AbstractProductB *CreateProductB() {
        return new ConcreteProductB1();
    }
};

class ConcreteFactory2 : public AbstractFactory {
public:
    virtual AbstractProductA *CreateProductA() {
        return new ConcreteProductA2();
    }

    virtual AbstractProductB *CreateProductB() {
        return new ConcreteProductB2();
    }
};

int main() {
    ConcreteFactory1 *factory1 = new ConcreteFactory1();
    AbstractProductA *productA1 = factory1->CreateProductA();
    AbstractProductB *productB1 = factory1->CreateProductB();

    delete productA1;
    delete productB1;
    delete factory1;

    ConcreteFactory2 *factory2 = new ConcreteFactory2();
    AbstractProductA *productA2 = factory2->CreateProductA();
    AbstractProductB *productB2 = factory2->CreateProductB();

    delete productA2;
    delete productB2;
    delete factory2;
}
