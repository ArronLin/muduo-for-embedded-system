#ifndef MUDUOEMB_NET_MUTEX_H
#define MUDUOEMB_NET_MUTEX_H

#include <pthread.h>
#include <assert.h>
#include <base/Uncopyable.h>
#include <base/CurrentThread.h>

namespace muduoEmb
{

class MutexLock : Uncopyable
{
  public:
    MutexLock()
      : holder_(0)
    {
      int ret = pthread_mutex_init(&mutex_, NULL);
      assert(ret == 0); (void)ret;
    }
    ~MutexLock()
    {
      assert(holder_ == 0);
      int ret = pthread_mutex_destroy(&mutex_);
      assert(ret == 0); (void)ret;
    }

    bool isLockedByThisThread()
    {
      return holder_ == CurrentThread::tid();
    }

    void assertLocked()
    {
      assert(isLockedByThisThread());
    }

    void lock()
    {
      pthread_mutex_lock(&mutex_);
      holder_ = CurrentThread::tid();
    }

    void unlock()
    {
      holder_ = 0;
      pthread_mutex_unlock(&mutex_);
    }

    pthread_mutex_t* getPthreadMutex()
    {
      return &mutex_;
    }
    
  private:
    pthread_mutex_t mutex_;
    pid_t holder_;
};

class MutexLockGuard : Uncopyable
{
  public:
    explicit MutexLockGuard(MutexLock& mutex)
      : mutex_(mutex)
    {
      mutex_.lock();
    }

    ~MutexLockGuard()
    {
      mutex_.unlock();
    }
    
  private:
    MutexLock& mutex_;
};

}

#endif

