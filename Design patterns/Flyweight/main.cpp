#include <iostream>
#include <unordered_map>

using namespace std;

class Flyweight {
public:
    Flyweight(const string &intrinsicState) : intrinsicState_(intrinsicState) {
        cout << "Flyweight[" << getIntrinsicState() << "] built" << endl;
    }

    virtual void operation(const string &) = 0;

    string getIntrinsicState() const {
        return intrinsicState_;
    }

private:
    string intrinsicState_;
};

class ConcreteFlyweight : public Flyweight {
public:
    ConcreteFlyweight(const string &intrinsicState) : Flyweight(intrinsicState) {}

    void operation(const string &extrinsicState) {
        cout << "Flyweight[" << getIntrinsicState() << "][" << extrinsicState << "] does operation" << endl;
    }
};

class FlyweightFactory {
public:
    ~FlyweightFactory() {
        for (auto &flyweight : mapFlyweight_) {
            delete flyweight.second;
        }
    }

    Flyweight *getFlyweight(const string &intrinsicState) {
        auto ptr = mapFlyweight_.find(intrinsicState);
        if (ptr == mapFlyweight_.end()) {
            ptr = mapFlyweight_.emplace(intrinsicState, new ConcreteFlyweight(intrinsicState)).first;
        }
        return ptr->second;
    }

private:
    unordered_map<string, Flyweight *> mapFlyweight_;
};

int main() {
    FlyweightFactory *flyweightFactory = new FlyweightFactory();
    Flyweight *flyweight1 = flyweightFactory->getFlyweight("A");
    Flyweight *flyweight2 = flyweightFactory->getFlyweight("B");
    Flyweight *flyweight3 = flyweightFactory->getFlyweight("A");

    flyweight3->operation("1");

    delete flyweightFactory;
}
