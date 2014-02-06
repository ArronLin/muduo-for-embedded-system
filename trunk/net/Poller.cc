#include <net/Poller.h>
#include <cstdio>
#include <cassert>
#include <net/Channel.h>

using namespace muduoEmb;
using namespace muduoEmb::net;

Poller::Poller(EventLoop* loop)
  : ownerLoop_(loop)
{
}

Poller::~Poller()
{
}

int Poller::poll(int timeoutMs, ChannelList* activeChannels)
{
  int numEvents = ::poll(&*pollfds_.begin(), pollfds_.size(), timeoutMs);

  if (numEvents > 0) {
    fprintf(stderr, "%d events happended\n", numEvents);
    fillActiveChannels(numEvents, activeChannels);
  }
  else if (numEvents == 0)
  {
    fprintf(stderr, "nothing happended\n");
  }
  else
  {
    abort();
  }

  return 0;
}

void Poller::fillActiveChannels(int numEvents, ChannelList* activeChannels)
{
  for (PollFdList::const_iterator pfd = pollfds_.begin();
        pfd != pollfds_.end() && numEvents > 0; ++pfd)
  {
    if (pfd->revents > 0)
    {
      --numEvents;
      ChannelMap::const_iterator ch = channels_.find(pfd->fd);
      assert(ch != channels_.end());
      Channel *channel = ch->second;
      channel->set_revents(pfd->revents);
      activeChannels->push_back(channel);
    }
  }
}

void Poller::updateChannel(Channel* channel)
{
  assertInLoopThread();
  
  if (channel->index() < 0)
  {
    assert(channels_.find(channel->fd()) == channels_.end());
    struct pollfd pfd;
    pfd.fd = channel->fd();
    pfd.events = channel->events();
    pfd.revents = 0;
    pollfds_.push_back(pfd);
    int idx = pollfds_.size() - 1;
    channel->set_index(idx);
    channels_[pfd.fd] = channel;
  }
  else
  {
    assert(channels_.find(channel->fd()) != channels_.end());
    assert(channels_[channel->fd()] == channel);
    int idx = channel->index();
    assert(idx >= 0 && idx < static_cast<int>(pollfds_.size()));
    struct pollfd& pfd = pollfds_[idx];
    assert(pfd.fd == channel->fd() || pfd.fd == -1);
    pfd.events = channel->events();
    pfd.revents = 0;

    if (channel->isNoneEvent())
    {
      pfd.fd = -1;
    }
    else
    {
      pfd.fd = channel->fd();
    }
  }
}

