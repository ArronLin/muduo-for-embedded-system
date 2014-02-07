#include <base/CurrentThread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <cstdio>

namespace muduoEmb
{
namespace CurrentThread
{

__thread int t_cacheTid;
__thread char t_tidString[32];
__thread const char* t_threadName;

}
}

namespace detail
{

pid_t gettid()
{
  return static_cast<pid_t>(::syscall(SYS_gettid));
}

}

using namespace muduoEmb;
void CurrentThread::cacheTid()
{
  if (t_cacheTid == 0)
  {
    t_cacheTid = detail::gettid();
    snprintf(t_tidString, sizeof(t_tidString), "%5d ", t_cacheTid);
  }
}

bool CurrentThread::isMainThread()
{
  return tid() == ::getpid();
}


