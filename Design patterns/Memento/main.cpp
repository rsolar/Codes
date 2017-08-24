#include <iostream>
#include <vector>

using namespace std;

typedef string State;

class Memento {
public:
    State get(int id) const {
        if (id >= size()) {
            throw std::runtime_error("wrong memento id");
        }
        return states_[id];
    }

    size_t size() const {
        return states_.size();
    }

    int add(const State &state) {
        states_.emplace_back(state);
        return static_cast<int>(size()) - 1;
    }

private:
    vector<State> states_;
};

class Originator {
public:
    State getState() const {
        return state_;
    }

    void setState(const State &state) {
        state_ = state;
    }

    int saveState(Memento *memento) {
        return memento->add(getState());
    }

    void restoreState(Memento *memento, int id) {
        setState(memento->get(id));
    }

private:
    State state_;
};


int main() {
    Originator *originator = new Originator();
    Memento *memento = new Memento();

    originator->setState("A");
    int stateA = originator->saveState(memento);
    cout << "Originator state: " << originator->getState() << endl;

    originator->setState("B");
    int stateB = originator->saveState(memento);
    cout << "Originator state: " << originator->getState() << endl;

    originator->restoreState(memento, stateA);
    cout << "Originator state: " << originator->getState() << endl;

    originator->restoreState(memento, stateB);
    cout << "Originator state: " << originator->getState() << endl;

    delete memento;
    delete originator;
}
