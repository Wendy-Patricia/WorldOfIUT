# Compiler
CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lncurses

# Targets
TARGET = WorldOfIUT

# Object files
OBJS = WorldOfIUT.o cmd.o mobile.o game.o exits.o location.o stack.o ui.o

# Dependencies
all: $(TARGET)

# Compile target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Individual dependencies
location.o: location.c location.h stack.h exits.h
stack.o: stack.c stack.h location.h
exits.o: exits.c exits.h
cmd.o: cmd.c cmd.h game.h exits.h mobile.h stack.h
mobile.o: mobile.c mobile.h exits.h
game.o: game.c game.h mobile.h exits.h location.h stack.h
ui.o: ui.c ui.h cmd.h game.h
WorldOfIUT.o: WorldOfIUT.c ui.h game.h cmd.h exits.h mobile.h location.h stack.h

# Clean up
clean:
	/bin/rm -f *.o $(TARGET)
