CPP=g++
CPPFLAGS=-std=c++11 -Wno-deprecated -g
LDFLAGS=-lglut -lglew -framework opengl $(shell pkg-config --cflags --libs opencv4)

.PHONY: clean

all:mid

mid: mid.cpp
	$(CPP) $(CPPFLAGS) $(LDFLAGS) $< -o $@

test: mid
	./mid

clean:
	rm -rf mid
