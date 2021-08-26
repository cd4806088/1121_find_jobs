//
// Created by chenda on 2020/12/30.
//

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

static  sem_t num1, num2, num3;

int id;

//以下线程函数使用的是sem_wait(),获取不到信号量时会阻塞当前线程
void* process_1(void *arg)
{
    for(int i = 0; i < 10; i++) {
        sem_wait(&num1);
        printf("aaa\n");
        sem_post(&num2);

    }
    return nullptr;
}

void* process_2(void *arg)
{
    for(int i = 0; i < 10; i++) {
        sem_wait(&num2);
        printf("bbb\n");
        sem_post(&num3);
    }
    return nullptr;
}

void* process_3(void *arg)
{
    for(int i = 0; i < 10; i++) {
        sem_wait(&num3);
        printf("ccc\n");
        sem_post(&num1);
    }
    return nullptr;
}

//以下线程函数使用的信号量函数为sem_wait(), 是信号量的非阻塞方式,获取信号量
//失败后不会阻塞线程,而是会执行程序其他部分
void* process_1_try_wait(void *arg)
{
    for(int i = 0; i < 10; i++) {
        if(sem_wait(&num1) == 0) {

            int *ptr = (int *)arg;
            cout << "process_1: " << *ptr << " " << ptr << endl;

            printf("aaa\n");
//            cout << "num1--i--val: " << num1.__align << endl;
            sem_post(&num2);
        } else {
            cout << "not get num1" << endl;
        }
    }
    cout << "process_1_try_wait died" << endl;
    return nullptr;
}

void* process_2_try_wait(void *arg)
{
    for(int i = 0; i < 10; i++) {
        if (sem_wait(&num2) == 0) {

            int *ptr = (int *)arg;
            *ptr += 1;
            cout << "process_2: " << *ptr << " " << ptr << endl;

            printf("bbb\n");
//            cout << "num2--i--val: " << num2.__align << endl;
            sem_post(&num3);
        } else {
            cout << "not get num2" << endl;
        }
    }
    cout << "process_2_try_wait died" << endl;
    return nullptr;
}

void* process_3_try_wait(void *arg)
{
    cout << "before--num3--i--val: " << num3.__align << endl;
    for(int i = 0; i < 10; i++) {
        if (sem_wait(&num3) == 0) {

            int *ptr = (int *)arg;
            *ptr -= 19;
            cout << "process_3: " << *ptr << " " << ptr << endl;

            printf("ccc\n");
            cout << "num3--i--val: " << num3.__align << endl;
            sem_post(&num1);
        } else {
            cout << "not get num3" << endl;
        }
    }
    cout << "process_3_try_wait died" << endl;
    return nullptr;
}

int main() {
    pthread_t tid_1, tid_2, tid_3;

    sem_init(&num1, 0, 1);
    sem_init(&num2, 0, 0);
    sem_init(&num3, 0, 0);

    int cd = 100;
    int *ptr = &cd;
    cout << "main: " << ptr << endl;

    pthread_create(&tid_1, NULL, &process_1, NULL);
    pthread_create(&tid_2, NULL, &process_2, NULL);
    pthread_create(&tid_3, NULL, &process_3, NULL);

//    pthread_create(&tid_1, NULL, &process_1_try_wait, ptr);
//    pthread_create(&tid_2, NULL, &process_2_try_wait, ptr);
//    pthread_create(&tid_3, NULL, &process_3_try_wait, ptr);

//    cout <<"test" << endl;\

    cout << "please press enter to stop" << endl;
    getchar();

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);
    pthread_join(tid_3, NULL);

    cout << "main thread runs after sun threads end" << endl;

//    cout << "num1 val: "<< num1.__align << endl;
//    cout << "num2 val: "<< num2.__align << endl;
//    cout << "num3 val: "<< num3.__align << endl;


    sem_destroy(&num1);
    sem_destroy(&num2);
    sem_destroy(&num3);

    return 0;
}