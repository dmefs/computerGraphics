CPP=g++
CPPFLAGS=-std=c++11 -Wno-deprecated -g
LDFLAGS=-lglut -lglew -framework opengl $(shell pkg-config --cflags --libs opencv4)

.PHONY: clean

all:lab7

lab7: lab7.cpp
	$(CPP) $(CPPFLAGS) $(LDFLAGS) $< -o $@

test: lab7
	./lab7

clean:
	rm -rf lab7
