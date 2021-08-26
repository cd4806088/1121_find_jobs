//
// Created by chenda on 2021/1/5.
//

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#define UNIX_DOMAIN "/tmp/unix.str"
#define UNIX_CLIENT "/tmp/unix_client.str"

using namespace std;

int main() {
    int sock_fd;
    struct sockaddr_un server_addr, client_addr;
    char sendbuf[20] = "manmanlai";

    sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    unlink(UNIX_CLIENT);
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strcpy(client_addr.sun_path, UNIX_CLIENT);
    if (bind(sock_fd,(struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
        cout << "bind client failed" << endl;
        return -1;
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, UNIX_DOMAIN);
    if (connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        cout << "connect failed" << endl;
        return -1;
    }
    write(sock_fd, sendbuf, strlen(sendbuf));

    getchar();
    close(sock_fd);
    return 0;
}