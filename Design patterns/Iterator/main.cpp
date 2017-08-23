#include <iostream>
#include <vector>

using namespace std;

typedef int Item;

class ConcreteIterator;

template<class T>
class Container {
public:
    virtual T getItem(int index) const;

    virtual void addItem(const T &item);

    virtual size_t size() const;

    virtual ConcreteIterator getIterator() = 0;

private:
    vector<T> items_;
};

class ConcreteContainer : public Container<Item> {
public:
    ConcreteIterator getIterator();
};

template<class T>
class Iterator {
public:
    Iterator(Container<T> *container);

    virtual T next() = 0;

    virtual bool hasNext() = 0;

protected:
    Container<T> *container_;
};

class ConcreteIterator : public Iterator<Item> {
public:
    ConcreteIterator(ConcreteContainer *concreteContainer);

    Item next();

    bool hasNext();

private:
    int index_;
};

template<class T>
T Container<T>::getItem(int index) const {
    return items_[index];
}

template<class T>
void Container<T>::addItem(const T &item) {
    items_.emplace_back(item);
}

template<class T>
size_t Container<T>::size() const {
    return items_.size();
}

ConcreteIterator ConcreteContainer::getIterator() {
    return ConcreteIterator(this);
}

template<class T>
Iterator<T>::Iterator(Container<T> *container) : container_(container) {}

ConcreteIterator::ConcreteIterator(ConcreteContainer *concreteContainer) : Iterator(concreteContainer), index_() {}

Item ConcreteIterator::next() {
    return container_->getItem(index_++);
}

bool ConcreteIterator::hasNext() {
    return index_ < container_->size();
}

int main() {
    ConcreteContainer *container = new ConcreteContainer();
    container->addItem(1);
    container->addItem(2);
    container->addItem(3);
    container->addItem(4);
    container->addItem(5);

    cout << "Container: ";
    for (ConcreteIterator iterator = container->getIterator(); iterator.hasNext();) {
        cout << iterator.next() << ' ';
    }
    cout << endl;

    delete container;
}
