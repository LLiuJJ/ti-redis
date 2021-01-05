#pragma once

#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <memory>
#include <atomic>
#include <functional>

#define INVALID_SOCKET (int)(~0)
#define SOCKET_ERROR (-1)
#define INVALID_PORT (-1)

struct SocketAddr
{
    SocketAddr()
    {
        Clear();
    }

    SocketAddr(const SocketAddr& other)
    {
        memcpy(&addr_, &other.addr_, sizeof(addr_));
    }

    SocketAddr& operator= (const SocketAddr& other)
    {
        if (this != &other)
            memcpy(&addr_, &other.addr_, sizeof(addr_));

        return *this;
    }

    SocketAddr(const sockaddr_in& addr)
    {
        Init(addr);
    }

    SocketAddr(const std::string& ipport)
    {
        std::string::size_type p = ipport.find_first_of(':');
        std::string ip = ipport.substr(0, p);
        std::string port = ipport.substr(p + 1);

        Init(ip.c_str(), static_cast<uint16_t>(std::stoi(port)));
    }

    SocketAddr(uint32_t netip, uint16_t netport)
    {
        Init(netip, netport);
    }

    SocketAddr(const char* ip, uint16_t hostport)
    {
        Init(ip, hostport);
    }

    void Init(const sockaddr_in& addr)
    {
        memcpy(&addr_, &addr, sizeof(addr));
    }

    void Init(uint32_t netip, uint16_t netport)
    {
        addr_.sin_family = AF_INET;
        addr_.sin_addr.s_addr = netip;
        addr_.sin_port = netport;
    }

    void Init(const char* ip, uint16_t hostport)
    {
        addr_.sin_family = AF_INET;
        addr_.sin_addr.s_addr = ::inet_addr(ip);
        addr_.sin_port = htons(hostport);
    }

    void Clear() { memset(&addr_, 0, sizeof(addr_)); }

    sockaddr_in addr_;
};
