PROGRAMS := main
GCC := g++
CFLAGS := -g -Wall -Wpedantic
LDFLAGS := -lncurses
OBJS := snake.o game.o snakegame.o

all: $(PROGRAMS)

$(PROGRAMS): $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) $(LDFLAGS)  main.cpp -o $@

$(OBJS): %.o: %.cpp %.hpp
	$(GCC) $(CFLAGS) $(LDFLAGS) -c $<

clean:
	rm $(PROGRAMS) $(OBJS)

.PHONY: all clean
