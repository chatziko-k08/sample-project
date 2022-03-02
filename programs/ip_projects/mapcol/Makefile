# paths
LIB = ../../../lib
INCLUDE = ../../../include

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)
LDFLAGS = -lm

# Αρχεία .o
OBJS = mapcol.o coloring.o $(LIB)/k08.a

# Το εκτελέσιμο πρόγραμμα
EXEC = mapcol

# Ορίσματα για make run
ARGS = < Balkans.txt


$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

# Για να φτιάξουμε το k08.a, τρέχουμε το make στο lib directory.
$(LIB)/k08.a:
	$(MAKE) -C $(LIB) k08.a

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind: $(EXEC)
	valgrind ./$(EXEC) $(ARGS)
