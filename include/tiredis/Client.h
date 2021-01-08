#pragma once

#include "StreamSocket.h"
#include "UnboundedBuffer.h"
#include "ProtoParser.h"
#include <pingcap/Exception.h>
#include <pingcap/kv/Scanner.h>
#include <pingcap/kv/Snapshot.h>
#include <pingcap/kv/Txn.h>
#include <tiredis/TiKvCluster.h>

namespace pingcap
{
namespace kv
{
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

class Client: public StreamSocket
{
private:
    PacketLength _HandlePacket(const char* msg, std::size_t len) override;

    UnboundedBuffer reply_;

    ProtoParser parser_;

    pingcap::kv::ClusterPtr test_cluster;

public:
    Client();

    void _Reset();

    void OnConnect() override;

};
