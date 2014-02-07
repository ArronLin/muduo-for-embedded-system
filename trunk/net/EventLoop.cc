#include <unistd.h>
#include <net/EventLoop.h>
#include <net/Poller.h>
#include <net/Channel.h>
#include <assert.h>
#include <base/Mutex.h>

using namespace muduoEmb;
using namespace muduoEmb::net;

namespace
{

const int kPollTimeMs = 10000;

__thread EventLoop* t_loopInThisThread = NULL;
}

EventLoop::EventLoop()
  : threadId_(CurrentThread::tid()),
    looping_(false),
    quit_(false),
    poller_(new Poller(this))
{
  if (t_loopInThisThread)
  {
    abort();
  }
  else
  {
    t_loopInThisThread = this;
  }
}

EventLoop::~EventLoop()
{
  assert(!looping_);
  t_loopInThisThread = NULL;
}

void EventLoop::loop()
{
  assert(!looping_);
  assertInLoopThread();
  looping_ = true;
  
  while (!quit_)
  {
    activeChannels_.clear();
    poller_->poll(kPollTimeMs, &activeChannels_);

    for (ChannelList::const_iterator ch = activeChannels_.begin();
          ch != activeChannels_.end(); ++ch)
    {
      (*ch)->handleEvent();
    }
  }
  
  looping_ = false;
}

void EventLoop::update(Channel* channel)
{
  poller_->updateChannel(channel);
}

