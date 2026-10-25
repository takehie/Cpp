CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = image.exe
SOURCES = main.cpp commands.cpp timer.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES)
    $(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
    rm -f $(TARGET)