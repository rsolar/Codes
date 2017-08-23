#include <iostream>

using namespace std;

class Receiver {
public:
    void action() {
        cout << "Receiver::action()" << endl;
    }
};

class Command {
public:
    virtual void execute() = 0;
};

class ConcreteCommand : public Command {
public:
    ConcreteCommand(Receiver *receiver) : receiver_(receiver) {}

    void execute() {
        cout << "ConcreteCommand::execute()" << endl;
        receiver_->action();
    }

private:
    Receiver *receiver_;
};

class Invoker {
public:
    Invoker(Command *command) : command_(command) {}

    void invoke() {
        cout << "Invoker::invoke()" << endl;
        command_->execute();
    }

private:
    Command *command_;
};

int main() {
    Receiver *receiver = new Receiver();
    Command *command = new ConcreteCommand(receiver);
    Invoker *invoker = new Invoker(command);

    invoker->invoke();

    delete invoker;
    delete command;
    delete receiver;
}
