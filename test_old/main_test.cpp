#include <iostream>
//#include <vector>
#include "Polymorphism_test.h"
//#include <stdio.h>
//#include<sys/types.h>
//#include <unistd.h>
//#include <stdlib.h>
#include <pthread.h>

using namespace std;
using namespace test;

int main() {
//    Polymorphism_test *test_p1 = new Polymorphism_test();
//    Polymorphism_test *test_p2 = new Polymorphism_test(888, 999);
//    sub sub_1 = sub();
//    sub sub_2 = sub(555,666,777);
//    Polymorphism_test *test_p3 = &sub_1;//
//    test_p3->print_b();
//    Polymorphism_test *test_p4 = &sub_2;
////    test_p4->print_c();//----------------这种多态方法只能调用基类与派生类共有的方法，派生类新定义的不可
//    test_p4->print_b();

//    std::vector<int> res = {1,2,3,4,5};
//    res.pop_back();
//    res.at(0);
//    std::cout << res.back() << res.front() << std::endl;

//    Polymorphism_test cd = Polymorphism_test();
//    cd.print_play();
//    cd.print_b();//执行不到

//    for(int i=0; i+20; i--)
//        std::cout << i << std::endl;
//    return 0;

//    大小端测试--1
    union test{
        int a;
        char b[sizeof(int)];
        struct {
            char c_a;
            short c_b;
        }c;
    };
    test t;
    t.a = 1;
    test t2;
    t2.a = 2;
    cout << &t.a << " " << (int *)&(t.b[3]) << " " << (int *)&(t.c.c_a) << " " << &(t.c.c_b) << endl;
    cout << &t2.a << " " << &t2.b << " " << (int *)&(t2.c.c_a) << " " << &(t2.c.c_b) << endl;
    if(t.b[0] == 1){
        std::cout << "小端" << std::endl;//低址存低位
    } else{
        std::cout << "大端" << std::endl;//低址存高位
    }
//    return 0;

    //大小端测试--2
    int a = 1;
    char *c = (char *)&a;
    cout << (int *)c << " " << &a << " " << &c << endl;
    if (*c == 1) {
        cout << "高有效字节存储在高地址,低有效字节存储在低位--小端" << endl;
    } else {
        cout << "高有效字节存储在低地址,低有效字节存储在高位--大端" << endl;
    }

    //似乎char类型的指针的值，也就是所指向空间的地址址是无法直接输出的。需要转化成(int *),才能正常输出
    char cc = 0;
    char * c_ptr = &cc;
    cout << c_ptr << endl;
    cout << (int *)c_ptr << " " << &c_ptr << endl;

    return 0;
}


//int main(void)
//{
//    int p1,p2;
//    while((p1 = fork()) == -1);
//    printf("create son process\n");
//    if(p1 == 0)
//    {
//        printf("son process print and then son process died\n");
//    } else{
//        while((p2 = fork()) == -1);
//        printf("create second son process\n");
//        if(p2 == 0)
//        {
//            printf("second son process print\n");
//        } else{
//            printf("it's their father's \n");
//        }
//    }
//    printf("each process executes this\n");
//    return 0;
//}


/*
author：Szymou
explain：
lockf(1,1,0)是锁上资源让该进程独自享用
lockf(1,0,0)是解锁资源，给其他进程用
下面的sleep用于该进程“休息一下”，休息的时候，其他进程可以用资源
这里的资源是个人认为是磁盘的缓冲区buffer
*/
//int main()//每次printf的时候，系统会先将需要输出的字符存在缓冲区buffer里面
//{
//    int p1,p2,i;
//    if(p1=fork())
//    {
//        lockf(1,1,0);//锁上buffer自己享用
//        for(i=0;i<3;i++)
//        {
//            printf("child %d\n",i);
//            /*老师的默认第二个lockf(1,1,0)是一直锁上的，结果会是先全部输出son012，再输出其他，其他进程同理*/
//            lockf(1,0,0);//解锁给另外的子进程
//            sleep(2);//其他子进程可以在父进程休眠的时候调用buffer使用
//        }
//    }
//    else
//    {
//        if(p2=fork())
//        {
//            lockf(1,1,0);//锁上buffer自己享用
//            for(i=0;i<3;i++)
//            {
//                printf("son %d\n",i);
//                lockf(1,0,0);
//                sleep(2);
//            }
//        }
//        else
//        {
//            lockf(1,1,0);//锁上buffer自己享用     //运行结果>>>>>
//            for(i=0;i<3;i++)                    //运行结果>>>>>
//            {
//                printf("daughter %d\n",i);
//                lockf(1,0,0);
//                sleep(2);
//            }
//        }
//    }return 0;
//}


/*
author：Szymou
explain：
父进程称为a进程
往下就是b、c、d进程
*/
//int main()
//{
//    int p1, p2, p3;
//    while((p1=fork()) == -1);
//    if(p1 != 0)
//    {
//        printf("process a(its id = %d, its father pid is %d)\n",getpid(), getppid());
//    } else{
//        printf("process b(its id = %d, its father pid is %d)\n",getpid(), getppid());
//        while((p2 = fork()) == -1);
//        if(p2 == 0)
//        {
//            printf("process c(its id = %d, its father pid is %d)\n",getpid(), getppid());
//            while((p3 = fork()) == -1);
//            if(p3 == 0)
//            {
//                printf("process d(its id = %d, its father pid is %d)\n",getpid(), getppid());
//            }
//        }
//    }
//    return 0;
//}


//int main(int argc, char *argv[])
//{
//    if (argc != 2) {
//        printf("argv[0]: %s\n",argv[0]);
//        fprintf(stderr, "Usage: %s <file-to-exec>\n", argv[0]);
//        exit(EXIT_FAILURE);
//    }
//    for(int i=0;i<argc;++i)
//    {
//        printf("argv[%d]: %s\n", i, argv[i]);
//    }
//    exit(EXIT_SUCCESS);
//}
