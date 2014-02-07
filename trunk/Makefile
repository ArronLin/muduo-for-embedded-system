TARGET=example/test
SRCS= example/main.cc \
			net/EventLoop.cc \
			net/Channel.cc \
			net/Poller.cc \
			base/Condition.cc \
			base/Thread.cc \
			net/Accepter.cc \
			net/InetAddress.cc

OBJS=$(patsubst %.cc, %.o, ${SRCS})
CFLAGS= -I. -g -Wall
LFLAGS= -lpthread -lrt

${TARGET}: ${OBJS}
	g++ $^ ${LFLAGS} -o $@

%.o: %.cc
	g++ -c ${CFLAGS} $^ -o $@

clean:
	rm -rf ${OBJS} ${TARGET}
