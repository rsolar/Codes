#include "scoped_ptr.h"

#include <iostream>

using namespace std;

class Sample {
public:
    Sample(int a = 0) : a_(a) {
        cout << "Sample::Sample()" << endl;
    }

    ~Sample() {
        cout << "Sample::~Sample()" << endl;
    }

    void display() {
        cout << "Sample::a=" << a_ << endl;
    }

private:
    int a_;
};

int main() {
    scoped_ptr<Sample> p(new Sample(5));
    p->display();
//    scoped_ptr<Sample> p1(p);
//    scoped_ptr<Sample> p2(move(p));
}
