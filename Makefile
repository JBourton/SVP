# Makefiles compile all files and headers in one, saving manually entering them into the command line

# Specify compiler
CC = gcc

# Specify complier flags
CFLAGS = -Wall -Wextra -std=c99

# State source files
SOURCES = main.c

# Set executable name
EXECUTABLE = runme

# Set default target - when `make` is ran, all commands associated with the 'all' target will be executed
all: $(EXECUTABLE)

# Link executable with sources
$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES)

# Remove runme file
clean:
	rm -f $(EXECUTABLE)
