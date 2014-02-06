#ifndef MUDUOEMB_NET_POLLER
#define MUDUOEMB_NET_POLLER

#include <vector>
#include <map>
#include <net/EventLoop.h>
#include <base/Uncopyable.h>
#include <poll.h>

namespace muduoEmb
{
namespace net
{

class Channel;

class Poller : Uncopyable
{
  public:
    typedef std::vector<Channel*> ChannelList;
    
    explicit Poller(EventLoop* loop);
    ~Poller();

    int poll(int timeoutMs, ChannelList* activeChannels);
    void updateChannel(Channel* channel);
    void assertInLoopThread() { ownerLoop_->assertInLoopThread(); }
  private:
    void fillActiveChannels(int numEvents, ChannelList* activeChannels);

    typedef std::vector<struct pollfd> PollFdList;
    typedef std::map<int, Channel*> ChannelMap;

    EventLoop* ownerLoop_;
    PollFdList pollfds_;
    ChannelMap channels_;
};

}
}


#endif

