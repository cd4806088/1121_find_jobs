//
// Created by chenda on 2021/2/28.
//

#include <iostream>
#include <vector>
#include <string.h>
#include <map>

using uint_t = unsigned int;
typedef unsigned int uint_t_1;

template <typename val>
using str_map_t = std::map<std::string, val>;
str_map_t<int> map1;

int array_sum(int (&arr)[10])
{
    int sum = 0;
    for (int i : arr) {
        sum += i;
    }
//    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i) {
//        sum += arr[i];
//    }
    return sum;
}

//int (&arr)[]是一种错误实现
/*void array_cout(int (&arr)[], int len) {
    for (int i = 0; i < len; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}*/

void array_cout(int *arr, int len) {
    for (int i = 0; i < len; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

//传入指针
void ptr_test (int *ptr)
{
    printf("--------传入指针的测试--------\n");
    printf("the val that formal param points to: %d\n", *ptr);
    printf("the formal param's val is: %x\n", ptr);
    printf("the formal param's addr is: %x\n", &ptr);
    *ptr = 100;
}

//传入指针的引用
void ptr_reference_test (int *&ptr)
{
    printf("------传入指针引用的测试--------\n");
    printf("the val that formal param points to: %d\n", *ptr);
    printf("the formal param's val is: %x\n", ptr);
    printf("the formal param's addr is: %x\n", &ptr);
    *ptr = 200;
}


int func_5()
{
    std::vector<int> k{ 1,2,3 };
    //std::vector<int>* p=&k;
    std::vector<int>* p;
    p = &k;

    (*p)[1] = 100;
    p->at(1) = 100;

    for (int i = 0; i < p->size(); i++)
    {
        std::cout << p->at(i) << ' ' << std::endl;
    }
    //1 1 1

    return 0;
}


int main () {
    //1:array_reference test
/*    int arr_1[10] = {1, 2, 3, 4};
    printf("the sum of arr is: %d\n", array_sum(arr_1));*/

    //2:ptr_test
/*    int a = 10;
    int *ptr1 = &a;
    ptr_test(ptr1);
    printf("------after 传入指针------\n");
    printf("the val that actual param points to: %d\n", *ptr1);
    printf("the actual param's val is: %x\n", ptr1);
    printf("the actual param's addr is: %x\n", &ptr1);
    ptr_reference_test(ptr1);
    printf("------after 传入指针引用------\n");
    printf("the val that actual param points to: %d\n", *ptr1);
    printf("the actual param's val is: %x\n", ptr1);
    printf("the actual param's addr is: %x\n", &ptr1);*/

    //3.
/*    std::vector<int> vec1;
    vec1.resize(10);
    memset(&vec1, 3, 10);//-----------似乎memset会破坏std::vector的内部的结构，导致出现内存泄露的问题。以后用std::vector、string之类的stl容器时要注意了。
    std::cout << vec1[4] << std::endl;
    int size = vec1.size();
    const int size = vec1.size();*/

/*    const int size = 10;
    bool flag[size] = {true};
    for (int i = 0; i < 10; ++i) {
        std::cout << flag[i] << std::endl;
    }*/


/*    std::vector<std::vector<int>>* ptr = new std::vector<std::vector<int>>();
//    auto* ptr = new std::vector<std::vector<int>>();
    ptr->at(0).empty();
    delete ptr;*/


    int myints[] = {1,2,3,4,5};
    array_cout(myints, 5);

    return 0;
}