CC = clang
CFLAGS = -g -Wall -Wextra
LDFLAGS =

SRCS = parse.c sat.c main.c
OBJS = $(SRCS:.c=.o)
EXEC = sat

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXEC)

parse.o: parse.c parse.h sat.h var_map.h
	$(CC) $(CFLAGS) -c parse.c

var_map.o: var_map.c var_map.h sat.h
	$(CC) $(CFLAGS) -c var_map.c

main.o: main.c parse.h var_map.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJS) $(EXEC)
