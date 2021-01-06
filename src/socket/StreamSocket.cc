#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/tcp.h>

#include <tiredis/StreamSocket.h>
#include <tiredis/Server.h>
#include <tiredis/NetThreadPool.h>


using std::size_t;

StreamSocket::StreamSocket()
{
}

StreamSocket::~StreamSocket()
{
}

bool StreamSocket::Init(int fd, const SocketAddr& peer)
{
    if (fd < 0)
        return false;

    peerAddr_ = peer;
    localSock_ = fd;
    SetNonBlock(localSock_);

    return true;
}

int StreamSocket::Recv()
{
    if (recvBuf_.Capacity() == 0)
    {
        recvBuf_.InitCapacity(64 * 1024); // 64k
    }
}
