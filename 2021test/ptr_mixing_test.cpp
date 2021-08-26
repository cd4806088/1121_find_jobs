//
// Created by chenda on 2021/8/17.
//

#include <bits/stdc++.h>

using namespace std;

class Base {
private:
    int num;
    string name;
public:
    Base(int x) : num(x) {}
    ~Base() {
        cout << "destroy base" << endl;
    }
    int& getNum() {
        return num;
    }
    virtual void saySomthing() {
        cout << "balabala" << endl;
    }
};

void func(Base* ptr) {
    cout << (int*)ptr << endl;
    cout << &(ptr->getNum()) << " " <<  ptr->getNum() << endl;
    delete ptr;
}

//以下函数线程不安全
int func2() {
    static int a;
    ++a;
    return a;
}

int main() {
    /*int *numPtr = new int(100);
    cout << (int*)numPtr << endl;
    func(reinterpret_cast<Base*>(numPtr));

    Base b(99);
    b.getNum() = 199;
    cout << b.getNum() << endl;*/

    for (int i = 0; i < 5; ++i) {
        cout << func2() << endl;
    }

    return 0;
}