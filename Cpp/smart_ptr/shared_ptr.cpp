#include "shared_ptr.h"

#include <iostream>
#include <vector>

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

void test1() {
    cout << "Enter test1()" << endl;
    shared_ptr<Sample> sp(new Sample());
    sp->display();
    cout << "Exit test1()" << endl;
}

shared_ptr<Sample> fun() {
    cout << "Enter fun()" << endl;
    shared_ptr<Sample> sp = make_shared<Sample>(1024);
    cout << "Exit fun()" << endl;
    return sp;
}

void test2() {
    cout << "Enter test2()" << endl;
    shared_ptr<Sample> retSp = fun();
    cout << "Exit test2()" << endl;
}

void test3() {
    cout << "Enter test3()" << endl;
    fun();
    cout << "Exit test3()" << endl;
}

void test4() {
    cout << "Enter test4()" << endl;

    shared_ptr<Sample> ptrA;

    cout << "ptrA=" << ptrA.get() << endl;
    cout << "ptrA.use_count()=" << ptrA.use_count() << endl << endl;

    if (ptrA) { // Impossible
        ptrA->display();
    } else {
        shared_ptr<Sample> ptrB = make_shared<Sample>(1024);

        if (ptrB) { ptrB->display(); }
        cout << "ptrB=" << ptrB.get() << endl;
        cout << "ptrB.use_count()=" << ptrB.use_count() << endl << endl;

        ptrA = ptrB;
        cout << "ptrA=" << ptrA.get() << endl;
        cout << "ptrA.use_count()=" << ptrA.use_count() << endl;
        cout << "ptrB=" << ptrB.get() << endl;
        cout << "ptrB.use_count()=" << ptrB.use_count() << endl << endl;

        vector<shared_ptr<Sample>> ptrs;
        ptrs.emplace_back(ptrA);
        cout << "ptrA=" << ptrA.get() << endl;
        cout << "ptrA.use_count()=" << ptrA.use_count() << endl;
        cout << "ptrs.back()=" << ptrs.back().get() << endl;
        cout << "ptrs.back().use_count()=" << ptrs.back().use_count() << endl << endl;
    }

    cout << "ptrA=" << ptrA.get() << endl;
    cout << "ptrA.use_count()=" << ptrA.use_count() << endl << endl;

    cout << "Exit test4()" << endl;
}

int main() {
    test1();
    cout << endl;
    test2();
    cout << endl;
    test3();
    cout << endl;
    test4();
}
