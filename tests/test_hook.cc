#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#include "sylar/sylar.h"
#include "sylar/hook.h"

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test_sleep() {
    sylar::IOManager iom(1);
    iom.schedule([]() {
        sleep(2);
        SYLAR_LOG_INFO(g_logger) << "sleep 2";
    });
    iom.schedule([]() {
        sleep(3);
        SYLAR_LOG_INFO(g_logger) << "sleep 3";
    });
    SYLAR_LOG_INFO(g_logger) << "finish";
}

void test_sock() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, "110.242.68.66", &addr.sin_addr.s_addr);

    SYLAR_LOG_INFO(g_logger) << "begin = " << time(0);
    int rt = connect(sock, (const sockaddr*)&addr, sizeof(addr));
    SYLAR_LOG_INFO(g_logger) << "connect rt = " << rt << ", errno=" << errno;
    SYLAR_LOG_INFO(g_logger) << "end = " << time(0);

    if(rt) {
        return;
    }

    const char data[] = "GET / HTTP/1.0\r\n\r\n";
    rt = send(sock, data, sizeof(data), 0);
    SYLAR_LOG_INFO(g_logger) << "send rt=" << rt << " errno=" << errno;

    if(rt <= 0) {
        return;
    }

    std::string buf;
    buf.resize(4096);

    rt = recv(sock, &buf[0], buf.size(), 0);
    SYLAR_LOG_INFO(g_logger) << "recv rt=" << rt << " errno=" << errno;

    if(rt <= 0) {
        return;
    }

    buf.resize(rt);
    SYLAR_LOG_INFO(g_logger) << buf;
}

int main(int argc, char** argv) {
    // test_sleep();
    sylar::IOManager iom;
    iom.schedule(test_sock);
    // test_sock();
    return 0;
}