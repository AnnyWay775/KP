CC = g++ #kompilacuia
LD = g++  #linking

CCFLAGS = 
LDFLAGS =

.PHONY: all
all: StaticL26 DynamicL26
.PHONY: static
static: StaticL26
.PHONY: dynamic
dynamic: DynamicL26

StaticL26: l26.o stackStat.o
	$(LD) $(LDFLAGS) -o StaticL26 l26.o stackStat.o
DynamicL26: l26.o stackDyn.o
	$(LD) $(LDFLAGS) -o DynamicL26 l26.o stackDyn.o

l26.o : l26.cpp
	$(CC) $(CCFLAGS) -c l26.cpp

stackStat.o: stack.h stackStat.cpp
	$(CC) $(CCFLAGS) -c stackStat.cpp
stackDyn.o: stack.h stackDyn.cpp
	$(CC) $(CCFLAGS) -c stackDyn.cpp

.PHONY: clean
clean:
	rm -f *.o DynamicL26 StaticL26
	