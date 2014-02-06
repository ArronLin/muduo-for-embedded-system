#include <base/Condition.h>
#include <errno.h>

using namespace muduoEmb;

// returns true if time out, false otherwise.
bool Condition::waitForSeconds(int seconds)
{
  struct timespec abstime;
  clock_gettime(CLOCK_REALTIME, &abstime);
  abstime.tv_sec += seconds;
  return ETIMEDOUT == pthread_cond_timedwait(&cond_, mutex_.getPthreadMutex(), &abstime);
}

