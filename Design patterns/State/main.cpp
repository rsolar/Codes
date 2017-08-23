#include <iostream>

using namespace std;

class Context;

class State {
public:
    virtual void handle(Context *context) = 0;

protected:
    State();
};

class ConcreteStateA : public State {
public:
    static State *getInstance();

    void handle(Context *context);

protected:
    ConcreteStateA();
};

class ConcreteStateB : public State {
public:
    static State *getInstance();

    void handle(Context *context);

protected:
    ConcreteStateB();
};

class Context {
public:
    Context();

    void setState(State *state);

    void request();

private:
    State *state_;
};

State::State() {}

State *ConcreteStateA::getInstance() {
    static ConcreteStateA instance;
    return &instance;
}

void ConcreteStateA::handle(Context *context) {
    cout << "State changed from A to B" << endl;
    context->setState(ConcreteStateB::getInstance());
};

ConcreteStateA::ConcreteStateA() {}

State *ConcreteStateB::getInstance() {
    static ConcreteStateB instance;
    return &instance;
}

void ConcreteStateB::handle(Context *context) {
    cout << "State changed from B to A" << endl;
    context->setState(ConcreteStateA::getInstance());
}

ConcreteStateB::ConcreteStateB() {}

Context::Context() : state_(ConcreteStateA::getInstance()) {}

void Context::setState(State *state) {
    state_ = state;
}

void Context::request() {
    state_->handle(this);
}

int main() {
    Context *context = new Context();
    context->request();
    context->request();
    context->request();
    delete context;
}
