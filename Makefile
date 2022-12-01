CC = gcc
CFLAGS = -std=c11 -Og -g -ggdb -Werror -Wpedantic -Wall -Wextra
TARGETS := aoc1

all: $(TARGETS)

$(TARGETS): %: %.c
	@echo "Building $@ ..."
	@$(CC) $(CFLAGS) $< -o $@
	@echo "Building $@ done."

clean:
	@echo "Cleanup: removing object files and executables..."
	@rm -fr *.o $(TARGETS)
	@echo "All clean."
