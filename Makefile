CXX=clang++
CXXFLAGS+=-std=c++11
LDFLAGS+=-stdlib=libc++

MAIN_EXECUTABLE=main
MAIN_SOURCES=main.cpp GenerateRandomNaturalSequence.cpp
MAIN_OBJECTS=$(MAIN_SOURCES:.cpp=.o)

TEST_EXECUTABLE=test
TEST_SOURCES=Test.cpp GenerateRandomNaturalSequence.cpp
TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)

$(MAIN_EXECUTABLE): unittest $(MAIN_OBJECTS)
	$(CXX) $(LDFLAGS) $(MAIN_OBJECTS) -o $@

$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CXX) $(LDFLAGS) $(TEST_OBJECTS) -o $@

.PHONY: tests

unittest: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

clean:
	rm -rf $(TEST_OBJECTS) $(TEST_EXECUTABLE) $(MAIN_OBJECTS) $(MAIN_EXECUTABLE)
