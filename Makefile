PROGRAMS := snake
GCC := g++
CFLAGS := -g -Werror -Wpedantic
LDFLAGS := -lncurses

all: $(PROGRAMS)

$(PROGRAMS): % : %.cpp
	$(GCC) $(CFLAGS) $^ $(LDFLAGS) -o $@

clean:
	rm $(PROGRAMS)

.PHONY: all clean
