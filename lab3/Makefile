CPP=g++
LDFLAGS=-lglut -lglew -framework opengl

.PHONY: clean

all:lab3

lab3: lab3.cpp
	$(CPP) $(LDFLAGS) $< -o $@

test: lab3
	./lab3

clean:
	rm -rf lab2

