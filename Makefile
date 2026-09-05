CC = gcc
# -g for Valgrind line numbers; warnings as errors; no optimization for clarity.
CFLAGS = -g -Wall -Wextra -Werror -O0 -std=c11

OBJS = main.c device.c list.c

list_demo: $(OBJS) device.h
	$(CC) $(CFLAGS) -o list_demo $(OBJS)

# Run under Valgrind; ANY memory error fails the build (the leak gate).
check: list_demo
	valgrind --leak-check=full --error-exitcode=1 ./list_demo

clean:
	rm -f list_demo
