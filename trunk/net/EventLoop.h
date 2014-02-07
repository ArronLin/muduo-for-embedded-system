#ifndef MUDUOEMB_NET_EVENTLOOP_H
#define MUDUOEMB_NET_EVENTLOOP_H

#include <base/Uncopyable.h>
#include <stdlib.h>
#include <vector>
#include <tr1/memory>
#include <base/CurrentThread.h>

namespace muduoEmb
{
namespace net
{

class Channel;
class Poller;

class EventLoop : Uncopyable
{
  public:
    EventLoop();
    ~EventLoop();

    typedef std::vector<Channel*> ChannelList;

    void assertInLoopThread()
    {
      if (!isInLoopThread())
      {
        abort();
      }
    }
    void loop();
    void update(Channel* channel);
    void quit() { quit_ = true; }

    bool isInLoopThread() { return threadId_ == CurrentThread::tid();}
  private:
    const pid_t   threadId_;
    bool          looping_;
    bool          quit_;
    std::tr1::shared_ptr<Poller> poller_;
    ChannelList   activeChannels_;
};

}
}

#endif

