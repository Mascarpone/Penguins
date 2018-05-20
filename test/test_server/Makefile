CFLAGS = -std=c99 -Wall -pedantic -Werror
LFLAGS =

OBJS += test_server.o \
	../../src/server/server.o \
	../../src/server/map/parseMap.o \
	../../src/server/graph/graph.o

PROG = test_server
CXX = gcc


all: $(PROG)

%.o: %.c 
	cp -R ../../rsc ./
	$(CXX) $(CFLAGS) -c $< -o $@

$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LFLAGS)

clean:
	rm -rf $(OBJS)
	rm -R -rf ./rsc
	rm -rf *~
	rm -rf $(PROG)
