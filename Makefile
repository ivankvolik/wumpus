CC=g++

#top level build command
wumpus.o: wumpus.cpp world.o events.o
	$(CC) -std=c++11 $? -o $@ -I.

world.o: world/src/world.cpp 
	$(CC) -std=c++11 -c $? -o $@ -I.
	
events.o: world/src/events.cpp
	$(CC) -std=c++11 -c $? -o $@ -I.
	
.PHONY: clean

clean:
	rm -f *.o