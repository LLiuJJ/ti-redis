//
//  TiRedis.cc
//
//
#include <pingcap/Exception.h>
#include <pingcap/kv/Scanner.h>
#include <pingcap/kv/Snapshot.h>
#include <pingcap/kv/Txn.h>
#include <tiredis/TiKvCluster.h>
#include <tiredis/TLogger.h>
#include <iostream>
#include <tiredis/ThreadPool.h>

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

void funHelloA() {
    for (int i = 0; i < 5; i ++){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "have fun from A " << i << std::endl;
    }
}

void funHelloB() {
    for (int i = 0; i < 5; i ++){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "have fun from B " << i << std::endl;
    }
}

int main(int ac, char* av[])
{
    LogManager::Instance().CreateLog(logFILE, "logs/tiredis.log");
    LogManager::Instance().Log().information("tiredis"); 
    LogManager::Instance().Log().information("my %d day!", 23);                                                
    pingcap::kv::ClusterPtr test_cluster;
    std::vector<std::string> pd_addrs{"127.0.0.1:2379"};
    test_cluster = createCluster(pd_addrs);
    pingcap::kv::Txn txn(test_cluster.get());
    txn.set("a", "a");
    txn.set("b", "b");
    txn.set("c", "c");
    txn.commit();
    pingcap::kv::Snapshot snap(test_cluster.get());
    std::cout << "get a:" << snap.Get("a") << std::endl;
    ThreadPool::Instance().ExecuteTask(funHelloA);
    ThreadPool::Instance().ExecuteTask(funHelloB);
    return 0;
}
