#ifndef __SYLAR_HTTP_HTTP_SERVER_H
#define __SYLAR_HTTP_HTTP_SERVER_H

#include "sylar/tcp_server.h"
#include "sylar/http/http_session.h"
#include "sylar/http/servlet.h"

namespace sylar {
namespace http {

class HttpServer : public TcpServer {
public:
    typedef std::shared_ptr<HttpServer> ptr;
    HttpServer(bool keepalive = false,
        sylar::IOManager* worker = sylar::IOManager::GetThis(),
        sylar::IOManager* accept_worker = sylar::IOManager::GetThis());

    ServletDispatch::ptr getServletDispatch() const { return m_dispatch;}
    void setServletDispatch(ServletDispatch::ptr v) { m_dispatch = v;}
protected:
    virtual void handleClient(Socket::ptr client) override;
private:
    bool m_isKeepalive;
    ServletDispatch::ptr m_dispatch;
};

}
}

#endif