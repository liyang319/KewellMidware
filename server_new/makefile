CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS= -lpthread
SOURCES=MainApp.cpp AppData.cpp UpperTcpServer.cpp UpperWorkerThread.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=MyTest

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
