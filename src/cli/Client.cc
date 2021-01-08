#include <tiredis/Client.h>
#include <tiredis/TLogger.h>
#include <tiredis/UnboundedBuffer.h>
#include <iostream>
#include <string>
#include <vector>

std::string vsprintf(const char* format, va_list args) {
    va_list argsCopy;
    va_copy(argsCopy, args);
    const int required = vsnprintf(nullptr, 0, format, args);
    va_end(args);
    if (required < 0) {
        va_end(argsCopy);
        return "";
    }
    std::vector< char > buffer(required + 1);
    const int result = vsnprintf(&buffer[0], required + 1, format, argsCopy);
    va_end(argsCopy);
    if (result < 0) {
        return "";
    }
    return std::string(buffer.begin(), buffer.begin() + required);
}

PacketLength Client::_HandlePacket(const char* start, std::size_t bytes)
{
    const char* const end   = start + bytes;
    const char* ptr  = start;
    // deal with packet
    LogManager::Instance().Log().information("pack size: %d", static_cast<int>(bytes));
    auto parseRet = parser_.ParseRequest(start, end);
    if (parseRet != ParseResult::ok)
    {
        return static_cast<PacketLength>(ptr - start);
    }
    const auto& params = parser_.GetParams();
    if (params.empty())
        return static_cast<PacketLength>(ptr - start);

    std::string cmd(params[0]);
    LogManager::Instance().Log().information("cmd: %s", cmd);
    for (auto it = params.begin(); it != params.end(); it ++)
    {
        LogManager::Instance().Log().information("param: %s", *it);
    }
    if(cmd == "set")
    {
        /* code */
        pingcap::kv::Txn txn(test_cluster.get());
        txn.set(params[1], params[2]);
        txn.commit();
        reply_.PushData("+OK\r\n", 5);
    } 
    else if 
    (cmd == "get")
    {
        pingcap::kv::Snapshot snap(test_cluster.get());
        std::string value = snap.Get(params[1]);
        std::string res = "$";
        res.append(std::to_string(value.size()));
        res.append("\r\n");
        res.append(value);
        res.append("\r\n");
        reply_.PushData(res.c_str(), res.size());
    }
    else
    {
        reply_.PushData("+OK\r\n", 5);
    }
    SendPacket(reply_);
    _Reset();
    return static_cast<PacketLength>(bytes);   
}

Client::Client()
{
    std::vector<std::string> pd_addrs{"127.0.0.1:2379"};
    test_cluster = createCluster(pd_addrs);
    _Reset();
}

void Client::_Reset()
{
    parser_.Reset();
    reply_.Clear();
}

void Client::OnConnect()
{

}
