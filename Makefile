CC=g++
#
# optimise: -O3
#
CCFLAGS=-g3 -Wall -pedantic -Wno-long-long -fmessage-length=0 -O3

O_FILES = parser.o test.o 

parser : $(O_FILES)
	@ echo "Linking ...";
	@ $(CC) $(CCFLAGS) -o parser $(O_FILES)

.SUFFIXES : .o .cpp
  
parser.cpp : parser.h

test.cpp : parser.h

