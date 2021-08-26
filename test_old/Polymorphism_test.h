//
// Created by chenda on 2020/10/21.
//

#ifndef TEST1_POLYMORPHISM_TEST_H
#define TEST1_POLYMORPHISM_TEST_H


namespace test{

class Polymorphism_test {
public:
    Polymorphism_test();
    Polymorphism_test(int a, int b):a_(a),b_(b){};
    void print_a();
    void print_b();
    void print_play();
    int cc_;

private:
    int a_;
    int b_;
};

class sub : public Polymorphism_test {
public:
    sub();
//    sub(int a, int b, int c):Polymorphism_test(a, b), c_(c){};
    sub(int a, int b, int c);
    void print_c();
//    class test::sub & operator=(class test::sub && );

private:
    int c_;
};

}//end of namespace

#endif //TEST1_POLYMORPHISM_TEST_H
