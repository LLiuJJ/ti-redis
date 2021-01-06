//
//  TiRedis.cc
//

#include <pingcap/Exception.h>
#include <pingcap/kv/Scanner.h>
#include <pingcap/kv/Snapshot.h>
#include <pingcap/kv/Txn.h>
#include <tiredis/TiKvCluster.h>
#include <tiredis/TLogger.h>
#include <tiredis/TiRedis.h>
#include <tiredis/Socket.h>
#include <tiredis/Client.h>
#include <iostream>

namespace pingcap
{
namespace kv
{

// Just for test purpose
struct TestTwoPhaseCommitter
{
private:
    TwoPhaseCommitter committer;

public:
    TestTwoPhaseCommitter(Txn *txn) : committer{txn} {}

    void prewriteKeys(Backoffer &bo, const std::vector<std::string> &keys) { committer.prewriteKeys(bo, keys); }

    void commitKeys(Backoffer &bo, const std::vector<std::string> &keys) { committer.commitKeys(bo, keys); }

    std::vector<std::string> keys() { return committer.keys; }

    void setCommitTS(int64_t commit_ts) { committer.commit_ts = commit_ts; }
};

}
}

TiRedis::TiRedis() : port_(0)
{
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
    LogManager::Instance().CreateLog(logFILE, "logs/tiredis.log");

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
    // LogManager::Instance().Log().information("tiredis");                                            
    // pingcap::kv::ClusterPtr test_cluster;
    // std::vector<std::string> pd_addrs{"127.0.0.1:2379"};
    // test_cluster = createCluster(pd_addrs);
    // pingcap::kv::Txn txn(test_cluster.get());
    // txn.set("a", "a");
    // txn.set("b", "b");
    // txn.set("c", "c");
    // txn.commit();
    // pingcap::kv::Snapshot snap(test_cluster.get());
    // std::cout << "get a:" << snap.Get("a") << std::endl;
    return 0;
}
