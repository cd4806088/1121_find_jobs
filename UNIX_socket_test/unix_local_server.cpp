//
// Created by chenda on 2021/1/5.
//

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#define UNIX_DOMAIN "/tmp/unix.str"

using namespace std;

int main() {
    int listen_fd,conn_fd;
    socklen_t clientlen;
    struct sockaddr_un clientaddr, serveraddr;
    char recvbuf[20] = {0};

    listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    unlink(UNIX_DOMAIN);
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sun_family = AF_UNIX;
    strcpy(serveraddr.sun_path, UNIX_DOMAIN);

    string str1 = serveraddr.sun_path;
    cout << serveraddr.sun_path << endl;
    cout << sizeof(serveraddr.sun_path) << endl;
    cout << str1.size() << endl;
    int len1 = str1.size();
    char *tmp = new char[len1 + 1];
    strcpy(tmp, str1.c_str());
    cout << tmp << endl;
    delete []tmp;

    if (bind(listen_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1) {
        cout << "bind listen socket error" << endl;
        return  -1;
    }
    if (listen(listen_fd, 1) == -1) {
        cout << "listen socket error" << endl;
        return -1;
    }

    clientlen = sizeof(clientaddr);
    cout << "after listen" << endl;
    conn_fd = accept(listen_fd, (struct sockaddr *)&clientaddr, &clientlen);
    cout << "accepted" << endl;

    string str2 = clientaddr.sun_path;
    cout << clientaddr.sun_path << endl;
    cout << str2.size() <<endl;
    cout << sizeof(clientaddr.sun_path) << endl;
    int len2 = str2.size();
    char *tmp2 = new char[len2 + 1];
    strcpy(tmp2, str2.c_str());
    cout << tmp2 << endl;
    delete []tmp2;



//    下面的方法由于没有在字符串结尾添加"\0"，所以输出会有乱码
//    cout << clientaddr.sun_path << endl;
////    string str = "clientaddr.sun_path";
//    string str = clientaddr.sun_path;
//    cout << sizeof(clientaddr.sun_path) << " " << sizeof(str) << " " << str.size() << " " << sizeof(str.c_str())
//    << " " << strlen(str.c_str()) << endl;
//    cout << str.c_str() << endl;
////    int len = sizeof(str.c_str());
//    int len = strlen(str.c_str());
//    for (int i = 0; i < len; ++i) {
//        char tmp = str.c_str()[i];
//        cout << tmp << endl;
//    }
////    printf("%s", str.c_str());
//    cout << "server pid: " << getpid() << ", " << "clientaddress is: " << string(clientaddr.sun_path).c_str() << endl;

    read(conn_fd, recvbuf, sizeof(recvbuf));
    cout << "recvbuf: " << string(recvbuf) << endl;

    getchar();
    close(conn_fd);
    close(listen_fd);
    return 0;
}

