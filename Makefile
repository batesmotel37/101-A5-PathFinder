#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 4
#
#  make                     makes FindPath
#  make GraphClient         makes GraphClient
#  make clean               removes binaries
#  make checkComponents     tests FindComponents on in3
#  make checkTest           tests GraphTest for memory leaks
#  make submit              submits all 7 files (GraphTest.c,Graph.c,Graph.h,
#                            List.h,List.c,FindPath.c,README,and this file) to
#                            Prof. Tantalo's pa4 directory
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full
SUBMITS        = ${HEADERS} ${BASE_SOURCES} Makefile README FindComponents.c GraphTest.c
SUBMITDIR      = cmps101-pt.f14 pa5

FindComponents : FindComponents.o $(BASE_OBJECTS)
	$(LINK) FindComponents FindComponents.o $(BASE_OBJECTS)

GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

FindComponents.o : FindComponents.c $(HEADERS)
	$(COMPILE) FindComponents.c

GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) FindComponents GraphTest FindComponents.o GraphTest.o $(BASE_OBJECTS)

checkComponents : FindComponents
	$(MEMCHECK) FindComponents in3 junk3

checkTest : GraphTest
	$(MEMCHECK) GraphTest

submit : ${SUBMITS}
	submit ${SUBMITDIR} ${SUBMITS}
