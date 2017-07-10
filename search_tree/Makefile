CXXFLAGS = -std=c++11 -g -Wall -O2
CXXFLAGS += $(INCLUDE)
CXX = g++
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET = test

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -ltcmalloc

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf *.o $(TARGET)
