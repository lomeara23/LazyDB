EXECUTABLE := $(shell basename $(CURDIR))

SOURCES := *.cpp

INCLUDES := -I ../include
EXT := out
CC := g++

all:
	$(CC) $(INCLUDES) $(SOURCES) -o $(EXECUTABLE).$(EXT)

realclean:
	find . -type f -name "*.o" -exec rm '{}' \;
	find . -type f -name "*.out" -exec rm '{}' \;
	find . -type f -name "*.exe" -exec rm '{}' \;

test:
	make all
	clear
	./$(EXECUTABLE).$(EXT)

test2:
	echo $(EXECUTABLE)