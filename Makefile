CC = gcc
CFLAGS = -std=c11 -Og -g -ggdb -Werror -Wpedantic -Wall
TARGETS := aoc1 aoc2 aoc3

all: $(TARGETS)

$(TARGETS): %: %.c
	@echo "Building $@ ..."
	@$(CC) $(CFLAGS) $< -o $@
	@echo "Building $@ done."

clean:
	@echo "Cleanup: removing object files and executables..."
	@rm -fr *.o $(TARGETS)
	@echo "All clean."
