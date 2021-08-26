//
// Created by chenda on 2021/5/31.
//

#include <string>
#include <iostream>

using namespace std;

template <typename T>
class SharedPtr {
private:
    int* count;
    T* ptr;

public:
    //空构造函数，空指针
    SharedPtr() : count(nullptr), ptr(nullptr) {}
    //构造函数，count必须new出来
    SharedPtr(T* p) : count(new int(1)), ptr(p) {}
    //拷贝构造函数，使其引用次数加一，两个智能指针的count指针指向的内存一致(把other指向的内存的地址传递)
    //在类内，如果包含同一class的传参，是可以访问传参的private成员的
    //SharedPtr(SharedPtr<T>& other) : count(&(++*(other.count))), ptr(other.ptr) {}
    //上面的拷贝构造函数还可以这样写
    SharedPtr(SharedPtr<T>& other) {
        ++*(other.count);
        count = other.count;
        ptr = other.ptr;
    }
    //定义运算符* && -> 不能算重载
    T* operator->() {return ptr;}
    T& operator*() {return *ptr;}
    //重载operator =
    //如果被赋值的SharedPtr已经有对象，则让其引用数减1并判断是否为0(来决定是否调用delete)，然后将新调用的对象引用次数+1
    SharedPtr<T>& operator = (SharedPtr<T>& other) {
        if (this == &other) return *this;
        ++*(other.count);
        if (this->ptr && 0 == --*(this->count)) {
            delete count;
            count = nullptr;
            delete ptr;
            ptr = nullptr;
            cout << "delete ptr" << endl;
        }
        this->count = other->count;
        this->ptr = other->count;
        return *this;
    }
    //析构函数，引用计数减1是否为0,来决定是否调用delete
    ~SharedPtr() {
        if (ptr && 0 == --*count) {
            delete count;
            count = nullptr;
            delete ptr;
            ptr = nullptr;
            cout << "delete ptr" << endl;
        }
    }

    int getref() {
        return *count;
    }
};

void function(char array[5]) {
    cout << sizeof(array) << endl;
}

template<typename T>
class bualbua : public SharedPtr<T> {

};

int main() {
    char* ptr = new char[5];
    char array[5] = {1,2,3,4,5};
    ptr = array;
    cout << (int)*(array + 2) << endl;
    cout << (int)*(ptr + 2) << endl;
    cout << sizeof(array) << endl;
    function(array);//当数组名当作形参传递给调用函数后，就失去了原有特性，退化成指针
    return 0;
}