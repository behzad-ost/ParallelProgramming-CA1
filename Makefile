CC=g++
CFLAGS=-msse3 -g -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0
CPP_FILES=$(wildcard src/*.cpp)
OBJ_FILES=$(patsubst src/%.cpp,obj/%.o,$(CPP_FILES))

all: mlp

mlp: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf mlp obj/*
