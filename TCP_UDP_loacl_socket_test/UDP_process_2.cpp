//
// Created by chenda on 2021/1/6.
//
#include <iostream>
#include <sys/socket.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PROCESS_2_RECV_IP "127.0.0.254"
#define PROCESS_2_SEND_IP "127.0.0.1"
#define PROCESS_2_RECV_PORT 8001
#define PROCESS_2_SEND_PORT 8000

using namespace std;

//void (*signal(int sig, void (*func)(int)))(int);

int main() {

    //本机进程间通信无需指定ip 只需要指定端口

    int socket_fd;
    struct sockaddr_in process_2_recv_sockaddr, process_2_send_sockaddr;
    bzero(&process_2_recv_sockaddr, sizeof(process_2_recv_sockaddr));
    process_2_recv_sockaddr.sin_family = AF_INET;
    process_2_recv_sockaddr.sin_port = htons(PROCESS_2_RECV_PORT);
//    process_2_recv_sockaddr.sin_addr.s_addr = inet_addr(PROCESS_2_RECV_IP);
    bzero(&process_2_send_sockaddr, sizeof(process_2_send_sockaddr));
    process_2_send_sockaddr.sin_family = AF_INET;
    process_2_send_sockaddr.sin_port = htons(PROCESS_2_SEND_PORT);
//    process_2_send_sockaddr.sin_addr.s_addr = inet_addr(PROCESS_2_SEND_IP);
    char recvbuf[100] = {};
    char sendbuf[] = "hiahiahia, i'm not ok";

    //非阻塞模式
    socket_fd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    //阻塞模式
    //socket_fd = socket(AF_INET, SOCK_DGRAM , 0);
    if (bind(socket_fd, (struct sockaddr *)&process_2_recv_sockaddr, sizeof(process_2_recv_sockaddr)) == -1) {
        cout << "bind socket failed" << endl;
        return -1;
    }

    cout << "process_2 begins to receive msg..." << endl;
    int len = sizeof(process_2_send_sockaddr);
    for (int i = 0; i < 10; ++i) {
        int recv_size = recvfrom(socket_fd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&process_2_send_sockaddr, (socklen_t *)&len);
        cout << "recv_size: " << recv_size << endl;
        if (recv_size == -1) {
            cout << "process_2 failed to recv msg at: " << i << endl;
//            continue;
        } else {
            cout << "process_2 recv msgs for " << i << " time" << ", msg is: " << recvbuf << endl;
        }
        if (sendto(socket_fd, sendbuf, sizeof(sendbuf), 0, (struct sockaddr *)&process_2_send_sockaddr, sizeof(process_2_send_sockaddr)) == -1) {
            cout << "process_2 failed to reply process_1" << endl;
//            continue;
        } else {
            cout << "process_2 replied process_1" << endl;
        }
        sleep(1);
    }
    cout << "wait for pressing Enter to stop" << endl;\
    getchar();

    close(socket_fd);
    return 0;
}

