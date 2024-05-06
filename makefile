CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=MainApp.cpp NodeThread.cpp ComThread.cpp UpperTcpClient.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=MyTest

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
