# Specify compiler
CC = gcc

# Specify complier flags
CFLAGS = -Wall -Wextra -std=c99

# State source files
SOURCES = main.c svp_structs.c lll.c command_line.c svp_application.c

HEADERS = svp_structs.h lll.h command_line.h svp_application.h

# Set executable name
EXECUTABLE = runme

# Set default target - when `make` is ran, all commands associated with the 'all' target will be executed
all: $(EXECUTABLE)

# Link executable with sources
$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) -lm

# Remove runme file
clean:
	rm -f $(EXECUTABLE)
