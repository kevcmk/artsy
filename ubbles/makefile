CC = g++
CFLAGS = -c --std=c++11
LDFLAGS = 

SOURCES = ubbles.cpp 
OBJECTS = $(SOURCES:.cpp=.o)

CFLAGS += `pkg-config --cflags opencv`
LDFLAGS += `pkg-config --libs opencv`

EXECUTABLE = ubbles

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)
