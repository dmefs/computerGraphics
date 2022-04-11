CPP=g++
LDFLAGS=-lglut -lglew -framework opengl

.PHONY: clean

all:lab4

lab4: lab4.cpp
	$(CPP) $(LDFLAGS) $< -o $@

test: lab4
	./lab4

clean:
	rm -rf lab4

