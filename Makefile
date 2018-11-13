CC      = g++
LDLIBS  = -std=c++14 -O0 -lglfw -lGL -lGLEW -lfreetype
LDFLAGS = -ggdb -Wall -pedantic
CFLAGS  = -std=c++14 -O0 -ggdb -I./src -I./libs/imgui -I/usr/include/freetype2/ -I../core

SRCDIR  = src
SRCDIR2 = libs/imgui ../core
SRCEXT  = cpp
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
SOURCES += $(shell find $(SRCDIR2) -type f -name *.$(SRCEXT))

OBJECTS= $(SOURCES:.cpp=.o)
EXECUTABLE=build/gt3d

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LDLIBS)


.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
