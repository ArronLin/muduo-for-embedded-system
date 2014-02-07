#include <net/InetAddress.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <cstdio>

using namespace muduoEmb;
using namespace muduoEmb::net;

InetAddress::InetAddress(const std::string& addr, uint16_t port)
{
  memset(&inetAddr_, 0, sizeof(inetAddr_));
	inetAddr_.sin_family = AF_INET;
  int ret = inet_pton(AF_INET, addr.c_str(), &inetAddr_.sin_addr.s_addr);
	if (ret != 1)
	{
		inetAddr_.sin_addr.s_addr = htonl(INADDR_ANY);	
	}
	inetAddr_.sin_port = htons(port);
}

InetAddress::InetAddress(uint16_t port)
{
	memset(&inetAddr_, 0, sizeof(inetAddr_));
	inetAddr_.sin_family = AF_INET;
	inetAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
	inetAddr_.sin_port = htons(port);
}

std::string InetAddress::toIp() const
{
	char ipbuf[16] = "INVALID";
	memset(ipbuf, 0, sizeof(ipbuf));
	inet_ntop(AF_INET, &inetAddr_.sin_addr.s_addr, 
			ipbuf, sizeof(ipbuf));
	
	return ipbuf;
}

std::string InetAddress::toIpPort() const
{
	char ipPort[32] = "INVALID";
	memset(ipPort, 0, sizeof(ipPort));
	inet_ntop(AF_INET, &inetAddr_.sin_addr.s_addr, 
										ipPort, sizeof(ipPort));
	char portBuf[10];
	memset(portBuf, 0, sizeof(portBuf));
	snprintf(portBuf, sizeof(portBuf), ":%u", 
			ntohs(inetAddr_.sin_port));
	strcat(ipPort, portBuf);

	return ipPort;
}

