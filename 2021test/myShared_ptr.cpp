//
// Created by chenda on 2021/4/10.
//

#include <string>
#include <iostream>

using namespace std;

template <typename T>
class SharedPtr {
public:
    //空构造函数，空指针
    explicit SharedPtr() : count(nullptr), ptr(nullptr) {}
    //构造函数，count必须new出来
    //注意此处，使用同一个指针变量初始化智能指针的话会产生重复释放内存，会产生段错误
    explicit SharedPtr(T* p) : count(new int(1)), ptr(p) {}
    //拷贝构造函数，使其引用次数加一，两个智能指针的count指向的内存一致
    //在类内，如果包含同一class的传参，是可以访问传参的private成员的
    explicit SharedPtr(SharedPtr<T>& other) : count(&(++*(other.count))), ptr(other.ptr) {}
    //上面的拷贝构造函数还可以这样写
    /*
        explicit SharedPtr(SharedPtr<T>& other) {
            ++(*(other.count));
            count = other.count;
            ptr = other.ptr;
        }
    */

    //定义运算符 * && ->实现指针功能，不能算重载
    T* operator->() {return ptr;}
    T& operator*() {return *ptr;}

    //重载operator =
    //如果被赋值的SharedPtr已经有对象，则让其引用对象次数减1并判断引用是否为0,（是否调用delete）,然后将新调用的对象次数加1
    SharedPtr<T>& operator = (SharedPtr<T>& other) {
        if (this == &other) return *this;
        ++*(other.count);

        /*
            if (ptr && 0 == --*count) {
                delete count;
                delete ptr;
                cout << "delete ptr" << endl;
            }
            count = other->count;
            ptr = other->ptr;
        */

        if (this->ptr && 0 == --*(this->count)) {
            delete count;
            delete ptr;
            cout << "delete ptr" << endl;
        }
        this->ptr = other.ptr;//注意此处！！！--shared_ptr是class,它指向一块内存，要区分好访问其成员变量和运算符的区别
        this->count = other.count;
        return *this;
    }
    //析构函数，使用引用计数减1并判断引用是否为0，来决定是否调用delete
    ~SharedPtr() {
        if (ptr && 0 == --*count) {
            delete count;
            count = nullptr;
            delete ptr;
            ptr = nullptr;
            cout << "delete ptr" << endl;
        }
    }

    int getRef() {
        return *count;
    }

private:
    int* count;
    T* ptr;
};


int main() {
//    SharedPtr<string> pstr(new string("abc"));
//    cout << "pstr: " << pstr.getRef() << " " << *pstr << endl;
//    cout << pstr->front() << endl;
//    SharedPtr<string> pstr2(pstr);
//    cout << "pstr: " << pstr.getRef() << " " << *pstr << endl;
//    cout << "pstr2: " << pstr2.getRef() << " " << *pstr2 << endl;
//    SharedPtr<string> pstr3(new string("chenda"));
//    cout << "pstr3: " << pstr3.getRef() << " " << *pstr3 << endl;
//
//    pstr2 = pstr3;
//    cout << "pstr: " << pstr.getRef() << " " << *pstr << endl;
//    cout << "pstr2: " << pstr2.getRef() << " " << *pstr2 << endl;
//    cout << "pstr3: " << pstr3.getRef() << " " << *pstr2 << endl;

    string* str_ptr = new string("abc");
    SharedPtr<string> smartPtr(str_ptr);
    //SharedPtr<string> smartPtr1(str_ptr);
    cout << str_ptr->front() << endl;
    cout << smartPtr->front() << endl;
    cout << sizeof(str_ptr) << endl;
    cout << sizeof(intptr_t) << endl;

    /*int size = 10;
    char* char_ptr = new char[size];*/

    return 0;
}