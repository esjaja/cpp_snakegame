PROGRAMS := snake
GCC := g++
CFLAGS := -g -Werror -Wpedantic
LDFLAGS := -lncurses
OBJS := game.o snakegame.o

all: $(OBJS) $(PROGRAMS)

$(PROGRAMS): % : %.cpp
	$(GCC) $(CFLAGS) $^ $(LDFLAGS) $(OBJS) -o $@

$(OBJS): %.o: %.cpp %.hpp
	$(GCC) $(CFLAGS) $(LDFLAGS) -c $^

clean:
	rm $(PROGRAMS) $(OBJS)

.PHONY: all clean
