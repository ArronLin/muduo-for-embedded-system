#ifndef MUDUOEMB_NET_CONDITION
#define MUDUOEMB_NET_CONDITION

#include <pthread.h>
#include <assert.h>
#include <base/Mutex.h>

namespace muduoEmb
{

class Condition
{
  public:
    explicit Condition(MutexLock& mutex)
      : mutex_(mutex)
    {
      int ret = pthread_cond_init(&cond_, NULL);
      assert(ret == 0); (void)ret;
    }
    
    ~Condition()
    {
      int ret = pthread_cond_destroy(&cond_);
      assert(ret == 0); (void)ret;
    }

    // returns true if time out, false otherwise.
    bool waitForSeconds(int seconds);

    void wait()
    {
      pthread_cond_wait(&cond_, mutex_.getPthreadMutex());
    }

    void notify()
    {
      pthread_cond_signal(&cond_);
    }

    void notifyAll()
    {
      pthread_cond_broadcast(&cond_);
    }

  private:
    pthread_cond_t cond_;
    MutexLock& mutex_;
};

}

#endif

