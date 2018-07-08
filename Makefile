CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=EntryPoint.cpp dbconnector.cpp dbworker.cpp userinterface.cpp notemanager.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=notebook

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -rdynamic  $(LDFLAGS) $(OBJECTS) -o $@ -lmysqlclient 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ 
