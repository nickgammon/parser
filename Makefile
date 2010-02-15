CC=g++
#
# optimise: -O3
#
CCFLAGS=-g3 -Wall -pedantic -Wno-long-long -fmessage-length=0 -O3

O_FILES = parser.o test.o 

test: $(O_FILES)
	@ echo "Linking ...";
	@ $(CC) $(CCFLAGS) -o parser $(O_FILES)

o/%.o: %.cpp
	echo "  Compiling $@....";
	$(CC) -c $(CCFLAGS) $< -o $@

.cpp.o: parser.h
	$(CC) -c $(CCFLAGS) $<

