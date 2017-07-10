CXXFLAGS = -std=c++11 -g -Wall
INCLUDE = -I /home/xujiang/rs_engine/deps/nark-hashmap/ -I /home/xujiang/rs_engine/deps/nark-bone/
CXXFLAGS += $(INCLUDE)
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET = test

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf *.o $(TARGET)
