//
// Created by chenda on 2021/8/12.
//

#include <bits/stdc++.h>

using namespace std;

typedef void(*Fun)(void);
//typedef void(*)(void) Fun

class Base {
public:
    virtual void func1() {
        cout << "father->func1" << endl;
    }
    virtual void func2() {
        cout << "father->func2" << endl;
    }
};

class PangBing : public Base {

};

class ErGou : public Base {
public:
    virtual void func1() {
        cout << "Base->func1" << endl;
    }
};

int main() {
    Fun pFun = nullptr;

    Base base;
    cout << "Base虚函数表地址: " << (int*)(&base) << endl;
    cout << "Base虚函数表第一个函数地址" << (int*)(*(int*)(&base)) << endl;
    pFun = (Fun)*((int*)*(int*)(&base));
    pFun();
    cout << endl;

    PangBing bing;
    cout << "PangBing虚函数表地址: " << (int*)(&bing) << endl;
    cout << "PangBing虚函数表第一个函数地址" << (int*)(*(int*)(&bing)) << endl;
    pFun = (Fun)*((int*)*(int*)(&bing));
    pFun();
    cout << endl;

    ErGou gou;
    cout << "ErGou虚函数表地址: " << (int*)(&gou) << endl;
    cout << "ErGou虚函数表第一个函数地址" << (int*)(*(int*)(&gou)) << endl;
    pFun = (Fun)*((int*)*(int*)(&gou));
    pFun();
    cout << endl;

    ErGou gou2;
    cout << "gou2虚函数表地址: " << (int*)(&gou2) << endl;
    cout << "gou2虚函数表第一个函数地址" << (int*)(*(int*)(&gou2)) << endl;
    pFun = (Fun)*((int*)*(int*)(&gou));
    pFun();

    return 0;
}