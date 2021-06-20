PROGRAMS := main
GCC := g++
CFLAGS := -g -Wall -Wpedantic
LDFLAGS := -lncurses
OBJS := snake.o game.o snakegame.o snakemap.o

all: $(PROGRAMS)

$(PROGRAMS): $(OBJS) main.cpp
	$(GCC) $(CFLAGS) $(OBJS) $(LDFLAGS)  main.cpp -o $@

$(OBJS): %.o: %.cpp %.hpp
	$(GCC) $(CFLAGS) $(LDFLAGS) -c $<

clean:
	rm $(PROGRAMS) $(OBJS)

.PHONY: all clean
