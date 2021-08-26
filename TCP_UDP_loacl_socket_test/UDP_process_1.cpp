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
#define PROCESS_1_RECV_IP "127.0.0.1"
#define PROCESS_1_SEND_IP "127.0.0.254"
#define PROCESS_1_RECV_PORT 8000
#define PROCESS_1_SEND_PORT 8001
//#define PROCESS_2_RECV_IP "127.0.0.254"
//#define PROCESS_2_SEND_IP "127.0.0.1"
//#define PROCESS_2_RECV_PORT 9000
//#define PROCESS_2_SEND_PORT 9001

using namespace std;

int main() {
    int socket_fd;
    struct sockaddr_in process_1_recv_sockaddr, process_1_send_sockaddr;
    bzero(&process_1_recv_sockaddr, sizeof(process_1_recv_sockaddr));
    process_1_recv_sockaddr.sin_family = AF_INET;
    process_1_recv_sockaddr.sin_port = htons(PROCESS_1_RECV_PORT);
//    process_1_recv_sockaddr.sin_addr.s_addr = inet_addr(PROCESS_1_RECV_IP);
    bzero(&process_1_send_sockaddr, sizeof(process_1_send_sockaddr));
    process_1_send_sockaddr.sin_family = AF_INET;
    process_1_send_sockaddr.sin_port = htons(PROCESS_1_SEND_PORT);
//    process_1_send_sockaddr.sin_addr.s_addr = inet_addr(PROCESS_1_SEND_IP);
    char sendbuf[] = "Hey! process_2, are you ok?"; //27 chars
    cout << "sendmsg size: " << sizeof(sendbuf) << endl; //28
    char recvbuf[100] = {};

    //非阻塞模式
    socket_fd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    //阻塞模式
    //socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (bind(socket_fd, (struct sockaddr *)&process_1_recv_sockaddr, sizeof(process_1_recv_sockaddr)) == -1) {
        cout << "bind socket failed" << endl;
        return -1;
    }

    cout << "wait for pressing Enter to send msg..." << endl;
    int len = sizeof(process_1_send_sockaddr);
    getchar();
    for (int i = 0; i < 10; ++i) {
        int send_size = sendto(socket_fd, sendbuf, sizeof(sendbuf), 0, (struct sockaddr *)&process_1_send_sockaddr, sizeof(process_1_send_sockaddr));
        cout << "send_size: " << send_size << endl;
        if (send_size == -1) {
            cout << "process_1 failed to send msg at: " << i << endl;
//            continue;
        } else {
            cout << "process_1 sends msgs for " << i << " time" << endl;
            cout << "process_1 wait for process_2's msg..." << endl;
        }
        if (recvfrom(socket_fd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&process_1_send_sockaddr, (socklen_t *)&len) == -1) {
            cout << "process_1 failed to get process_2's reply" << endl;
//            continue;
        } else {
            cout << "process_1 gets process_2's reply: " << recvbuf << endl;
        }
        sleep(1);
    }
    cout << "wait for pressing Enter to stop" << endl;
    getchar();

    close(socket_fd);
    return 0;
}
