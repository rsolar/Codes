#include <iostream>

using namespace std;

class Strategy {
public:
    virtual void algorithm() = 0;
};

class ConcreteStrategyA : public Strategy {
public:
    void algorithm() {
        cout << "ConcreteStrategyA::algorithm()" << endl;
    }
};

class ConcreteStrategyB : public Strategy {
public:
    void algorithm() {
        cout << "ConcreteStrategyB::algorithm()" << endl;
    }
};

class Context {
public:
    Context(Strategy *strategy) : strategy_(strategy) {}

    void setStrategy(Strategy *strategy) {
        strategy_ = strategy;
    }

    void request() {
        strategy_->algorithm();
    }

private:
    Strategy *strategy_;
};

int main() {
    Strategy *strategyA = new ConcreteStrategyA();
    Strategy *strategyB = new ConcreteStrategyB();
    Context *context = new Context(strategyA);

    context->request();
    context->setStrategy(strategyB);
    context->request();

    delete context;
    delete strategyA;
    delete strategyB;
}
