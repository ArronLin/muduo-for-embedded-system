#ifndef MUDUOEMB_NET_INETADDRESS_H
#define MUDUOEMB_NET_INETADDRESS_H

#include <stdint.h>
#include <string>
#include <netinet/in.h>

namespace muduoEmb
{
namespace net
{

class InetAddress
{
  public:
    explicit InetAddress(uint16_t port);
    InetAddress(const std::string& addr, uint16_t port);
    InetAddress(const struct sockaddr_in& inetAddr)
      : inetAddr_(inetAddr)
    {
    }

    std::string toIp() const;
    std::string toIpPort() const;

    const struct sockaddr_in& getSockAddrInet() const { return inetAddr_; }
    void setSockAddrInet(const struct sockaddr_in& inetAddr)
    { inetAddr_ = inetAddr; }

    uint32_t IpNetEndian() 
    { return inetAddr_.sin_addr.s_addr; }
		uint16_t PortNetEndian()
		{ return inetAddr_.sin_port; }
    
  private:
    struct sockaddr_in inetAddr_;
};

}
}

#endif

