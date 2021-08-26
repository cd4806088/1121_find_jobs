//
// Created by chenda on 2021/8/25.
//

#include <bits/stdc++.h>

using namespace std;

class Base {
public:
    int val;
    Base(int x) : val(x) {
        cout << "normal constructor was called" << endl;
    }
    Base(const Base& other) : val(other.val) {
        cout << "copy constructor was called" << endl;
    }
    Base& operator = (const Base& other){
        if (this == &other) return *this;
        this->val = other.val;
        cout << "assignment constructor was called" <<endl;
        return *this;
    }
};

Base func1() {
    Base B(3);
    cout << (int*)&B << endl;
    return B;
}

Base func2() {
    Base B(4);
    cout << (int*)&B << endl;
    return Base(B);
}

int main() {
    Base B1 = func1();
    cout << (int*)&B1 << endl;
    cout << endl;
    Base B2 = func2();
    cout << (int*)&B2 << endl;
    cout << endl;
    B2 = B1;
    return 0;
}