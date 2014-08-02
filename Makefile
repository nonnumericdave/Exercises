CC=clang++

MAIN_EXECUTABLE=main
MAIN_SOURCES=main.cpp GenerateRandomNaturalSequence.cpp
MAIN_OBJECTS=$(MAIN_SOURCES:.cpp=.o)

$(MAIN_EXECUTABLE): $(MAIN_OBJECTS)
	$(CC) $(LDFLAGS) $(MAIN_OBJECTS) -o $@

clean:
	rm -rf $(MAIN_OBJECTS) $(MAIN_EXECUTABLE)
