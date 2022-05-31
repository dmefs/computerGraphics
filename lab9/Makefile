CPP=g++
CPPFLAGS=-std=c++11 -Wno-deprecated -g
LDFLAGS=-lglut -lGL -lGLU

SRC=shadow.cpp
.PHONY: clean

all:lab9

lab9: $(SRC)
	$(CPP) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

test: lab9
	./lab9

clean:
	rm -rf lab9
