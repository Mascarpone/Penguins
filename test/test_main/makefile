CFLAGS = -ggdb -std=c99 -Wall -pedantic
LFLAGS = -rdynamic -lm -ldl `sdl2-config --cflags --libs` -lSDL2 -lSDL2_ttf

OBJS += ../../src/server/server.o \
	../../src/server/graph/graph.o \
	../../src/server/map/parseMap.o \
	../../src/server/graphic/display.o \
	../../src/server/graphic/draw.o \
	../../src/server/graphic/graphic.o \
	../../src/server/main.o

PROG = letsplay
CXX = gcc


.PHONY: clean

# linking the program.
$(PROG): $(OBJS)
	cp -R ../../rsc ./
	$(CXX) $(OBJS) -o $@ $(LFLAGS)

# compiling other source files.
%.o: %.c
	$(CXX) $(CFLAGS) -c $< -o $@

# cleaning everything that can be automatically recreated with "make".
clean:
	rm -rf $(OBJS)
	rm -R -rf ./rsc
	rm -rf *~
	rm -rf $(PROG)
