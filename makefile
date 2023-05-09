CXX = g++
CXXFLAGS = -std=c++11 -g -O2 -fsanitize=undefined -fsanitize=leak -fsanitize=address

all: build run

build: slidingBlock

run:
	./slidingBlock

slidingBlock: slidingBlock.cpp Grid.h Piece.h Movement.h 
	$(CXX) $(CXXFLAGS) -o slidingBlock slidingBlock.cpp

clean:
	rm -f slidingBlock *.o