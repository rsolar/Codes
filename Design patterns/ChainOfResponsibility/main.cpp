#include <iostream>

using namespace std;

class Handler {
public:
    Handler(Handler *successor = nullptr) : successor_(successor) {}

    Handler *getSuccessor() const {
        return successor_;
    }

    void setSuccessor(Handler *successor) {
        successor_ = successor;
    }

    virtual void handle() = 0;

private:
    Handler *successor_;
};

class ConcreteHandlerA : public Handler {
public:
    void handle() {
        if (getSuccessor() != nullptr) {
            cout << "ConcreteHandlerA passes the request to its successor" << endl;
            getSuccessor()->handle();
        } else {
            cout << "ConcreteHandlerA has to handle the request itself" << endl;
        }
    }
};

class ConcreteHandlerB : public Handler {
public:
    void handle() {
        if (getSuccessor() != nullptr) {
            cout << "ConcreteHandlerB passes the request to its successor" << endl;
            getSuccessor()->handle();
        } else {
            cout << "ConcreteHandlerB has to handle the request itself" << endl;
        }
    }
};

int main() {
    Handler *handler1 = new ConcreteHandlerA();
    Handler *handler2 = new ConcreteHandlerB();

    handler1->setSuccessor(handler2);
    handler1->handle();

    delete handler1;
    delete handler2;
}
