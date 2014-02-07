#ifndef MUDUOEMB_NET_CURRENTTHREAD_H
#define MUDUOEMB_NET_CURRENTTHREAD_H

namespace muduoEmb
{
namespace CurrentThread
{

extern __thread int t_cacheTid;
extern __thread char t_tidString[32];
extern __thread const char* t_threadName;

void cacheTid();
inline int tid()
{
  if (t_cacheTid == 0)
  {
    cacheTid();
  }

  return t_cacheTid;
}

inline char* tidString()
{
  return t_tidString;
}

inline const char* name()
{
  return t_threadName;
}

bool isMainThread();

}
}

#endif

