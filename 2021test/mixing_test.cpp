//
// Created by chenda on 2021/3/21.
//
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>

#include <pthread.h>
#define STRING(x) #x#x
#define TEXT(x) "Name"#x"__"
#define CLASS_NAME(name) class##name
#define MERGE(a,b) a##b##a

using namespace std;

class father {
public:
    father() {
        std::cout << "default constructor is called" << std::endl;
    }
    father(int x) {
        a = x;
    }
    //father(int x) : a(x) {} //列表初始化不算是函数重载，
    father(const father& f) {
        std::cout << "copy constructor is called" << std::endl;
    }
    virtual void say() {
        std::cout << "father said " << std::endl;
    }
private:
    int a;
};

class son : public father {
public:
    //即使使用virtual覆盖父类虚函数，同样也是覆盖
    virtual void say() {
        std::cout << "son virtual said" << std::endl;
    }
};

class grandson : public son {
public:
    void say() {
        std::cout << "grandson virtual said" << std::endl;
    }
};

class A {
public:
    /*virtual void func() = 0;*/
    virtual void func() {
        std::cout << "kkk" << std::endl;
    }
    void func1() {
        std::cout << "A::func1" << std::endl;
    }
};

class B : public A {
public:
    void func() {
        std::cout << "lll" << std::endl;
    }
    virtual void func(int x) {}
    void func1() {
        std::cout << "B::func1" << std::endl;
    }
};


void pro_func(void* arg) {
    printf("the val is: %n\n", (intptr_t)arg);
}

union endtest {
    int a;
    char c;
};

void func11(father f) {
    std::cout << "use transmission parameter" << std::endl;
}
father func12() {
    father f;
    std::cout << "临时变量地址: " << &f << std::endl;
    std::cout << "return value" << std::endl;
    return f;
}
father& func13() {
    father f;
    std::cout << "临时变量地址: " << &f << std::endl;
    std::cout << "return reference" << std::endl;
    return f;
}
father func14(const father& f) {
    std::cout << "传入参数地址: " << &f << std::endl;
    return f;
}

int fun21(father& f) {
    return 0;
}
int func21(const father& f) {
    return 0;
}

int& mymax(int& x, int& y) {
    if (x > y) return x;
    return y;
}

int main() {

    int x = 1;
    int y = 2;
    //int n = mymax(x, y * x);
    //cout << n << endl;

    /*int x = 1;
    int y = 2;
    x <<= y;
    cout << x << endl;

    unsigned char n = 0x80;
    n >>= 4;
    unsigned char buffer = 128;
    if ((int)(buffer & n) == 0) {
        cout << "buffer & n == 0" <<endl;
    }
    buffer |= n;
    if ((int)(buffer & n) != 0) {
        cout << "buffer & n != 0" <<endl;
    }
    cout << (int)n << endl;
    cout << (int)buffer << endl;*/

    //unsigned char* ptr = new unsigned char[2];

    return 0;
}

int main_old1() {
    /*A a;
    a.func1();
    B b;
    b.func1();
    A* a1 = new B();
    a1->func1();*/

    /*endtest test;
    test.a = 0x1234;
    std::cout << test.c << std::endl;//由此可见为小端
    std::cout << (int*)&test.a << " " << &test.c << std::endl;*/

    std::cout << "-----------------test begin-----------------" << std::endl;
    father f1;
    std::cout << "-----------------test1 begin-----------------" << std::endl;
    father f2 = f1;//
    std::cout << "-----------------test2 begin-----------------" << std::endl;
    func11(f1);
    std::cout << "-----------------test3 begin-----------------" << std::endl;
    father f3 = func12();
    std::cout << "返回值变量地址: " << &f3 << std::endl;
    std::cout << "-----------------test4 begin-----------------" << std::endl;
    father f4 = func13();
    std::cout << "返回引用变量地址: " << &f4 << std::endl;
    std::cout << "-----------------test5 begin-----------------" << std::endl;
    father f5 = func14(f4);
    std::cout << "返回变量地址: " << &f5 << std::endl;

    return 0;
}

int main_old()
{
//    int Jqm = 102;
//    printf("%s\n", STRING(Jqm));
//    printf("%s\n", TEXT(Jqm));
//    std::string classJqm = "Test_className";//------关键看这里的变量名字！！！
//    std::string Jqm1Jqm = "Test_Merge";
//    printf("%s\n", CLASS_NAME(Jqm).c_str());
//    printf("%s\n", MERGE(Jqm,1).c_str());
//
//
//    father* pfather = nullptr;
//    son son1;
//    grandson grandson1;
//    pfather = &son1;
//    pfather->say();
//    pfather = &grandson1;
//    pfather->say();

/*
    //绝了 (void*)是一个指针类型 空指针，既然是指针那么存的就是一个地址，大小要么是32,要么是64
    //在内存中，地址就可以用int(32位)，long long or unsigned long(64位)来表示----统一可以使用intptr_t
    //这种用法在多线程编程的线程函数中非常常见
    int i = 10;
    void* ptr = (void*)i;
    std::cout << (intptr_t)ptr << std::endl;
*/

/*
    son s1 = son();
    son s2 = son();
    auto vptr1 = (int*)&s1;
    auto vptr2 = (int*)&s2;
    auto vfunc_addr1 = *vptr1;
    auto vfunc_addr2 = *
*/

/*
    int num = 124;
    char num_c = (char)num;
    int num_1 = (int)num_c;
    char kongge = NULL;
    int kongge_num = (int)kongge;
    std::cout << num_c  << " " << num_1 << std::endl;
    std::cout << kongge  << " " << kongge_num << std::endl;
*/

//验证纯虚类相关
/*
    A a1;
    B b1;
    A* a2 =&b1;
    a2->func();
*/
    std::vector<int> vec{1,  6, 44, 46, 1, 2, 4, 7,88};
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << '\t';
    }
    std::cout << '\n'<< '\n';

    std::priority_queue<int, std::vector<int>, std::greater<int>> smallHeap_queue(vec.begin(), vec.end());
    while (!smallHeap_queue.empty()) {
        std::cout << smallHeap_queue.top() << '\t';
        smallHeap_queue.pop();
    }
    std::cout << '\n';

    std::priority_queue<int, std::vector<int>, std::less<int>> bigHeap_queue(vec.begin(), vec.end());
    while (!bigHeap_queue.empty()) {
        std::cout << bigHeap_queue.top() << '\t';
        bigHeap_queue.pop();
    }
    std::cout << '\n'<< '\n';


    std::multiset<int, std::greater<int>> set1(vec.begin(), vec.end());
    std::multiset<int, std::less<int>> set2(vec.begin(), vec.end());
    while (!set1.empty()) {
        std::cout << *(set1.begin()) << '\t';
        set1.erase(set1.begin());
    }
    std::cout << '\n';
    while (!set2.empty()) {
        std::cout << *(set2.begin()) << '\t';
        set2.erase(set2.begin());
    }
    std::cout << '\n'<< '\n';


    std::sort(vec.begin(), vec.end(), std::greater<int>());
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << '\t';
    }
    std::cout << '\n';

    std::sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << '\t';
    }
    std::cout << '\n';


    int a[10];
    //&a表示数组的指针，a表示数组名，是数组首元素地址
    int (*p)[10] = &a;

    int flag = 1;
    flag << 1;
    std::cout << flag << std::endl;



    return 0;
}

