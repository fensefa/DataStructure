CXXFLAGS = -std=c++11 -g -Wall
CXXFLAGS += $(INCLUDE)
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET = test

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf *.o $(TARGET)
