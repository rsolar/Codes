#include <iostream>
#include <unordered_map>

using namespace std;

class Mediator;

class Colleage {
public:
    Colleage(const string &name, Mediator *mediator);

    void setMediator(Mediator *mediator);

    virtual void sendMessage(const string &, const string &) = 0;

    virtual void receiveMessage(const string &, const string &) = 0;

protected:
    string name_;
    Mediator *mediator_;
};

class ConcreteColleageA : public Colleage {
public:
    ConcreteColleageA(const string &name, Mediator *mediator = nullptr);

    void sendMessage(const string &name, const string &message);

    void receiveMessage(const string &name, const string &message);
};

class ConcreteColleageB : public Colleage {
public:
    ConcreteColleageB(const string &name, Mediator *mediator = nullptr);

    void sendMessage(const string &name, const string &message);

    void receiveMessage(const string &name, const string &message);
};

class Mediator {
public:
    void registerColleage(const string &name, Colleage *colleage);

    virtual void operate(const string &name, const string &message) = 0;

protected:
    unordered_map<string, Colleage *> mapColleage_;
};

class ConcreteMediator : public Mediator {
public:
    void operate(const string &name, const string &message);
};

Colleage::Colleage(const string &name, Mediator *mediator) : name_(name), mediator_(mediator) {}

void Colleage::setMediator(Mediator *mediator) {
    mediator_ = mediator;
}

ConcreteColleageA::ConcreteColleageA(const string &name, Mediator *mediator) : Colleage(name, mediator) {}

void ConcreteColleageA::sendMessage(const string &name, const string &message) {
    if (mediator_== nullptr) {
        throw runtime_error("Mediator not set");
    }
    cout << name_ << " sends message to " << name << ": " << message << endl;
    mediator_->operate(name, message);
}

void ConcreteColleageA::receiveMessage(const string &name, const string &message) {
    cout << name_ << " receives message from " << name << ": " << message << endl;
}

ConcreteColleageB::ConcreteColleageB(const string &name, Mediator *mediator) : Colleage(name, mediator) {}

void ConcreteColleageB::sendMessage(const string &name, const string &message) {
    if (mediator_== nullptr) {
        throw runtime_error("Mediator not set");
    }
    cout << name_ << " sends message to " << name << ": " << message << endl;
    mediator_->operate(name, message);
}

void ConcreteColleageB::receiveMessage(const string &name, const string &message) {
    cout << name_ << " receives message from " << name << ": " << message << endl;
}

void Mediator::registerColleage(const string &name, Colleage *colleage) {
    mapColleage_.emplace(name, colleage);
    colleage->setMediator(this);
}

void ConcreteMediator::operate(const string &name, const string &message) {
    auto ptr = mapColleage_.find(name);
    if (ptr == mapColleage_.end()) {
        cout << "Colleage " << name << " not found" << endl;
        return;
    }
    ptr->second->receiveMessage(name, message);
}

int main() {
    Colleage *colleageA = new ConcreteColleageA("Alice");
    Colleage *colleageB = new ConcreteColleageB("Bob");
    Mediator *mediator = new ConcreteMediator();

    mediator->registerColleage("A", colleageA);
    mediator->registerColleage("B", colleageB);

    colleageA->sendMessage("B", "Hi");
    colleageB->sendMessage("A", "Hello");

    delete mediator;
    delete colleageA;
    delete colleageB;
}
