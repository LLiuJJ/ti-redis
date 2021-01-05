#pragma once

#include <errno.h>
#include <sys/socket.h>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "Server.h"
#include "NetThreadPool.h"
#include "ListenSocket.h"

namespace Internal
{

const int ListenSocket::LISTENQ = 1024;

ListenSocket::ListenSocket(int tag) :
    localPort_(INVALID_PORT),
    tag_(tag)
{
}

ListenSocket::~ListenSocket()
{
    Server::Instance()->DelListenSock(localSock_);
}

bool ListenSocket::Bind(const SocketAddr& addr)
{
    if (addr.Empty())
        return false;
    
    if (localSock_ != INVALID_SOCKET)
        return false;

    localPort_ = addr.GetPort();
    localSock_ = CreateTCPSocket();
    SetNonBlock(localSock_);
    SetNodelay(localSock_);
    SetReuseAddr(localSock_);
    SetRcvBuf(localSock_);
    SetSndBuf(localSock_);

    struct sockaddr_in serv = addr.GetAddr();

    int ret = ::bind(localSock_, (struct sockaddr*)&serv, sizeof serv);
    if (SOCKET_ERROR == ret)
    {
        CloseSocket(localSock_);
        return false;
    }
    ret = ::listen(localSock_, ListenSocket::LISTENQ);
    if (SOCKET_ERROR == ret)
    {
        CloseSocket(localSock_);
        return false;
    }

}

}