#include <iostream>
#include <unordered_set>

using namespace std;

class Observer;

class Subject {
public:
    virtual string getState() = 0;

    virtual void setState(const string &state) = 0;

    virtual void attach(Observer *observer);

    virtual void detach(Observer *observer);

    virtual void notify();

private:
    unordered_set<Observer *> observers_;
};

class ConcreteSubject : public Subject {
public:
    string getState();

    void setState(const string &state);

private:
    string state_;
};

class Observer {
public:
    Observer(Subject *subject, const string &name);

    virtual ~Observer();

    virtual void update() = 0;

protected:
    Subject *subject_;
    string subjectName_;
};

class ConcreteObserverA : public Observer {
public:
    ConcreteObserverA(Subject *subject, const string &name);

    ~ConcreteObserverA();

    void update();
};

class ConcreteObserverB : public Observer {
public:
    ConcreteObserverB(Subject *subject, const string &name);

    ~ConcreteObserverB();

    void update();
};

void Subject::attach(Observer *observer) {
    observers_.emplace(observer);
}

void Subject::detach(Observer *observer) {
    observers_.erase(observer);
}

void Subject::notify() {
    for (auto &observer : observers_) {
        observer->update();
    }
}

string ConcreteSubject::getState() {
    return state_;
}

void ConcreteSubject::setState(const string &state) {
    state_ = state;
    notify();
}

Observer::Observer(Subject *subject, const string &name) : subject_(subject), subjectName_(name) {
    subject_->attach(this);
}

Observer::~Observer() {
    subject_->detach(this);
}

ConcreteObserverA::ConcreteObserverA(Subject *subject, const string &name) : Observer(subject, name) {}

ConcreteObserverA::~ConcreteObserverA() {}

void ConcreteObserverA::update() {
    cout << "[ConcreteObserverA]update subject " << subjectName_ << " state: " << subject_->getState() << endl;
}

ConcreteObserverB::ConcreteObserverB(Subject *subject, const string &name) : Observer(subject, name) {}

ConcreteObserverB::~ConcreteObserverB() {}

void ConcreteObserverB::update() {
    cout << "[ConcreteObserverB]update subject " << subjectName_ << " state: " << subject_->getState() << endl;
}

int main() {
    Subject *subject = new ConcreteSubject();

    Observer *observerA = new ConcreteObserverA(subject, "A");
    subject->setState("1");

    Observer *observerB = new ConcreteObserverB(subject, "B");
    subject->setState("2");

    delete observerA;
    delete observerB;
    delete subject;
}
