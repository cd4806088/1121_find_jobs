//
// Created by chenda on 2021/3/10.
//

#include <iostream>
#include <memory>

int[]& func(void) {
    int* ptr = new int[3];
    ptr[0] = 88;
    ptr[1] = 58;
    return reinterpret_cast<int (&)[]>(*ptr);
}

int main() {
//    //1:----有内存泄漏：对于申请的数组动态内存，未定制deleter还是会存在内存泄漏
//   int* ptr1 = new int[5];
//    std::shared_ptr<int> p1(ptr1);//这里实际有内存泄漏，需要定制deleter
////    delete []ptr;//会重复释放一次内存而报错
//
//    //2:---无内存泄漏
//    int *ptr2 = new int[5];
//    std::shared_ptr<int> p12(ptr2, [](void* p_){delete [](int*)p_;});
//
//    //3：---无内存泄漏
//    int *ptr3 = new int[5];
//    std::shared_ptr<int> p3(ptr3, [](void*){});//实际上定制不存在实际操作的deleter意味着智能指针不进行内存释放
//    delete []ptr3;
//
//
//    int *ptr = new int[4];
//    ptr[1] = 11;
//    (*ptr) = 10;
////    (*ptr)[3] = 13;
//    for (int i = 0; i < 5; ++i) {
//        std::cout << ptr[i] << std::endl;
//    }
//    delete []ptr;


//    int val = 51;
//    char ch = (char)val;
//    char ch1 = 'a';
//    int val1 = (int)ch1;
//    std::cout << ch << " " << val1 << std::endl;

    auto ref = func();
    std::cout << ref[0] << ref[1] << std::endl;
    delete []ref;



    return 0;
}

