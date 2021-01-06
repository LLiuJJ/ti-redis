#pragma once

#include "StreamSocket.h"
#include "UnboundedBuffer.h"

class Client: public StreamSocket
{
private:
    PacketLength _HandlePacket(const char* msg, std::size_t len) override;

    UnboundedBuffer reply_;

public:
    Client();

    void _Reset();

    void OnConnect() override;

};
