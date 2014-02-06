#include <net/Channel.h>
#include <poll.h>
#include <net/EventLoop.h>

using namespace muduoEmb;
using namespace muduoEmb::net;

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop* loop,int fd)
  : loop_(loop),
    fd_(fd),
    events_(0),
    revents_(0),
    index_(-1)
{

}

void Channel::update()
{
  loop_->update(this);
}

void Channel::handleEvent()
{
  if (revents_ & (POLLERR | POLLNVAL)) {
    if (errorCallback_) errorCallback_();
  }
  if (revents_ & (POLLIN | POLLPRI | POLLRDHUP)) {
    if (readCallback_) readCallback_();
  }
  if (revents_ & POLLOUT)
  {
    if (writeCallback_) writeCallback_();
  }
}

