CPP=g++
LDFLAGS=-lglut -lglew -framework opengl

.PHONY: clean

all:lab2

lab2: lab2.cpp
	$(CPP) $(LDFLAGS) $< -o $@

test: lab2
	./lab2

clean:
	rm -rf lab2

