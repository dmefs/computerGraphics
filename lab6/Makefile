CPP=g++
CPPFLAGS=-Wno-deprecated -g
LDFLAGS=-lglut -lglew -framework opengl

.PHONY: clean

all:lab6

lab6: lab6.cpp
	$(CPP) $(CPPFLAGS) $(LDFLAGS) $< -o $@

test: lab6
	./lab6

clean:
	rm -rf lab6

