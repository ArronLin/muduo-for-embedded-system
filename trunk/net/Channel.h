#ifndef MUDUOEMB_NET_CHANNEL_H
#define MUDUOEMB_NET_CHANNEL_H

#include <tr1/functional>
#include <base/Uncopyable.h>

namespace muduoEmb
{
namespace net
{

class EventLoop;

class Channel : Uncopyable
{
  public:
    typedef std::tr1::function<void()> EventCallback;

    Channel(EventLoop* loop, int fd);

    void handleEvent();
    void setReadCallback(const EventCallback& cb)
    { readCallback_ = cb; }
    void setWriteCallback(const EventCallback& cb)
    { writeCallback_ = cb; }
    void setErrorCallback(const EventCallback& cb)
    { errorCallback_ = cb; }

    void enableReading()
    { events_ |= kReadEvent; update(); }
    void enableWriting()
    { events_ |= kWriteEvent; update(); }

    void set_revents(int revents)
    { revents_ = revents; }
    void set_index(int index)
    { index_ = index; }
    
    int fd() { return fd_; }
    int index() { return index_; }
    int events() { return events_; }

    bool isNoneEvent() { return events_ == kNoneEvent; }
    
  private:
    void update();

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop*  loop_;
    int         fd_;
    int         events_;
    int         revents_;
    int         index_;

    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
};

}
}

#endif

