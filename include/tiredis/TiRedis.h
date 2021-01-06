#include "Server.h"

#define VERSION "1.0.0"

class TiRedis : public Server
{
public:
    TiRedis();
    ~TiRedis();

    // bool ParseArgs(int ac, char* av[]);

private:
    std::shared_ptr<StreamSocket> _OnNewConnection(int fd, int tag) override;

    bool _Init() override;
    bool _RunLogic() override;
    bool _Recycle() override;

    unsigned short port_;
    
};
