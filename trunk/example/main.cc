#include <base/Uncopyable.h>
#include <net/EventLoop.h>
#include <net/Channel.h>
#include <iostream>
#include <base/Mutex.h>
#include <base/Condition.h>
#include <cstdio>
#include <pthread.h>
#include <unistd.h>

muduoEmb::net::EventLoop* g_loop = NULL;

#if 0
void stdRead()
{
  char buf[256];
  int ret = read(0, buf, sizeof(256));
  write(1, buf, ret);

  g_loop->quit();
}
#endif

bool signal = 0;
muduoEmb::MutexLock mutex;
muduoEmb::Condition cond(mutex);

void* threadFunc(void *p)
{
  while (true)
  {
    muduoEmb::MutexLockGuard guard(mutex);
    while (signal == 0)
    {
      cond.wait();
    }
    fprintf(stderr, "signal is %d\n", signal);
    signal = 0;
  }

  return NULL;
}

int main(int argc, char *argv[])
{
  #if 0
  muduoEmb::net::EventLoop loop;
  g_loop = &loop;
  muduoEmb::net::Channel stdChannel(&loop, 0);
  stdChannel.setReadCallback(stdRead);
  stdChannel.enableReading();

  muduoEmb::MutexLock mutex;
  
  {
    muduoEmb::MutexLockGuard guard1(mutex);
    muduoEmb::MutexLockGuard guard2(mutex);
    
    fprintf(stderr, "Run in here!!!- 1111\n");
  }

  fprintf(stderr, "Run in here!!!- 2222\n");
  
  loop.loop();
  #endif

  pthread_t threadId;
  pthread_create(&threadId, NULL, threadFunc, NULL);

  while (true)
  {
    {
      muduoEmb::MutexLockGuard guard(mutex);
      signal = 1;
      cond.notify();
    }
    ::sleep(1);
  }
  
  return 0;
}

