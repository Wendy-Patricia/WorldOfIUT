all: WorldOfIUT
CC=gcc
location.o: location.h
exits.o: exits.h
cmd.o: cmd.h game.h exits.h mobile.h
mobile.o: mobile.h exits.h
game.o: game.h mobile.h exits.h location.h
WorldOfIUT.o: cmd.h exits.h mobile.h game.h location.h
WorldOfIUT: WorldOfIUT.o cmd.o mobile.o game.o exits.o location.o
clean:
	/bin/rm *.o WorldOfIUT