CXX = g++
CXXFLAGS = -O2 -std=c++17 -pthread

TARGET = array-summary
SRC = array-summary.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

