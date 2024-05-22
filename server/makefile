CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS= -lpthread
SOURCES=server3.cpp AppData.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=MyTest

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
