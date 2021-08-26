//
// Created by chenda on 2020/10/21.
//
#include <iostream>
#include "Polymorphism_test.h"

using namespace std;

namespace test
{
    Polymorphism_test::Polymorphism_test() {
        a_ = 1;
        b_ = 2;
        cc_ = 100;
    }
    void Polymorphism_test::print_a() {
        cout << "the value of a_ is: " << a_ << endl;
    }
    void Polymorphism_test::print_b() {
        cout << "the value of b_ is: " << b_ << endl;
    }
    void Polymorphism_test::print_play()
    {
        std::cout << "是否不用实例化就可以输出呢？" << std::endl;
    }

    sub::sub() {
        c_ = 3;
    }
    sub::sub(int a, int b, int c) : Polymorphism_test(a, b), c_(c){

    }
    void sub::print_c() {
        cout << "the value of c_ is: " << c_ <<endl;
    }


}//end of namespace
