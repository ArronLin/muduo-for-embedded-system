#include <base/Uncopyable.h>
#include <net/EventLoop.h>
#include <net/Channel.h>
#include <iostream>

muduoEmb::net::EventLoop* g_loop = NULL;

void stdRead()
{
  char buf[256];
  int ret = read(0, buf, sizeof(256));
  write(1, buf, ret);

  g_loop->quit();
}

int main(int argc, char *argv[])
{
  muduoEmb::net::EventLoop loop;
  g_loop = &loop;
  muduoEmb::net::Channel stdChannel(&loop, 0);
  stdChannel.setReadCallback(stdRead);
  stdChannel.enableReading();
  
  loop.loop();
  
  return 0;
}

