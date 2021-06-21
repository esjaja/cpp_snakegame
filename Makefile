PROGRAMS := main

CXX := g++

HEADER := ./header
SOURCE := ./src

CXXFLAGS := -std=c++11 -g -Wall -Wpedantic -I$(HEADER) 
LDFLAGS := -lncurses 

OBJS := snake.o game.o snakegame.o snakemap.o

all: $(PROGRAMS)

$(PROGRAMS): $(OBJS) main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) main.cpp $(LDFLAGS)  

$(OBJS): %.o: $(SOURCE)/%.cpp $(HEADER)/%.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm $(PROGRAMS) $(OBJS)

.PHONY: all clean
