CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = huff_phase2
OBJS = main.o Scanner.o BST.o PriorityQueue.o utils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Scanner.hpp BST.hpp PriorityQueue.hpp utils.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Scanner.o: Scanner.cpp Scanner.hpp utils.hpp
	$(CXX) $(CXXFLAGS) -c Scanner.cpp

BST.o: BST.cpp BST.hpp
	$(CXX) $(CXXFLAGS) -c BST.cpp

PriorityQueue.o: PriorityQueue.cpp PriorityQueue.hpp utils.hpp
	$(CXX) $(CXXFLAGS) -c PriorityQueue.cpp

utils.o: utils.cpp utils.hpp
	$(CXX) $(CXXFLAGS) -c utils.cpp

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f input_output/*.tokens input_output/*.freq

.PHONY: all clean