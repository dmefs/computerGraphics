CPP=g++
LDFLAGS=-lglut -lglew -framework opengl

.PHONY: clean

all:lab5

lab5: lab5.cpp
	$(CPP) $(LDFLAGS) $< -o $@

test: lab5
	./lab5

clean:
	rm -rf lab5

