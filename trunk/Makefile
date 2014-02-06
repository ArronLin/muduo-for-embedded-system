TARGET=example/test
SRCS= example/main.cc \
			net/EventLoop.cc \
			net/Channel.cc \
			net/Poller.cc

OBJS=$(patsubst %.cc, %.o, ${SRCS})
CFLAGS= -I. -g -Wall

${TARGET}: ${OBJS}
	g++ $^ -o $@

%.o: %.cc
	g++ -c ${CFLAGS} $^ -o $@

clean:
	rm -rf ${OBJS} ${TARGET}
