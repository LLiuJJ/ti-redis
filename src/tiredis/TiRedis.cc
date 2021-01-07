//
//  TiRedis.cc
//

#include <tiredis/TLogger.h>
#include <tiredis/TiRedis.h>
#include <tiredis/Socket.h>
#include <tiredis/Client.h>
#include <iostream>

TiRedis::TiRedis() : port_(0) {
}

TiRedis::~TiRedis()
{
}

std::shared_ptr<StreamSocket> TiRedis::_OnNewConnection(int connfd, int tag)
{
    // new connection comming
    SocketAddr peer;
    Socket::GetPeerAddr(connfd, peer);

    auto cli(std::make_shared<Client>());
    if (!cli->Init(connfd, peer))
        cli.reset();
    return cli;
    
}

bool TiRedis::_Init()
{
    LogManager::Instance().CreateLog(logConsole, "logs/tiredis.log");

    SocketAddr addr("127.0.0.1", 8899);
    if (!Server::TCPBind(addr, 1)) {
         LogManager::Instance().Log().information("bind error");
        return false;
    }

    return true;
}

bool TiRedis::_RunLogic()
{
    return Server::_RunLogic();
}

bool TiRedis::_Recycle()
{
    // free resources
}

int main(int ac, char* av[])
{
    TiRedis svr;
    svr.MainLoop(false);

    return 0;
}
