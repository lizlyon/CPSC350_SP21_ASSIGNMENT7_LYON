# A simple Makefile for CPSC 350
#this Makefile goes your assignment directory

#change this to the correct assignment #
EXECUTABLE := assignment7

# the source files to be built
SOURCES := *.cpp

#stuff you don't need to worry about
EXT := exe
CC := g++

all:
	$(CC) $(SOURCES) -o $(EXECUTABLE).$(EXT)

realclean:
	find . -type f -name "*.o" -exec rm '{}' \;
	find . -type f -name "*.exe" -exec rm '{}' \;

# this line required by make - don't delete
