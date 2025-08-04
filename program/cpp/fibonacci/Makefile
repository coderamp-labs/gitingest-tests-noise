CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = fibonacci
SOURCE = fibonacci.cpp
HEADER = fibonacci.h

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SOURCE) $(HEADER)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

# Compile-time test to verify constexpr works
test-constexpr: $(SOURCE) $(HEADER)
	$(CXX) $(CXXFLAGS) -c $(SOURCE) -o /dev/null

help:
	@echo "Available targets:"
	@echo "  all          - Build the fibonacci program"
	@echo "  run          - Build and run the fibonacci program"
	@echo "  clean        - Remove built files"
	@echo "  test-constexpr - Test that constexpr compilation works"
	@echo "  help         - Show this help message" 