# Specify compiler
CC = gcc

# Specify complier flags
CFLAGS = -Wall -Wextra -std=c99

# State source files
SOURCES = main.c svp_structs.c lll.c command_line.c svp_application.c
TEST_SOURCE = known_svp_test.c
TEST_EXTRA_SOURCES = svp_structs.c lll.c svp_application.c

HEADERS = svp_structs.h lll.h command_line.h svp_application.h
TEST_HEADERS = svp_structs.h lll.h svp_application.h

# Set executable name
EXECUTABLE = runme
TEST_EXECUTABLE = testme

# Set default target - when `make` is ran, all commands associated with the 'all' target will be executed
all: $(EXECUTABLE)

# Link executable with sources
$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) -lm

# Remove runme file
clean:
	rm -f $(EXECUTABLE)

# Test the program
test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

# Build executable for testing
$(TEST_EXECUTABLE): $(TEST_SOURCE) $(TEST_EXTRA_SOURCES) $(TEST_HEADERS)
	$(CC) $(CFLAGS) -o $(TEST_EXECUTABLE) $(TEST_SOURCE) $(TEST_EXTRA_SOURCES) -lm


