# paths
LIB = ../../lib
INCLUDE = ../../include

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
override CFLAGS += -Wall -Werror -O3 -I$(INCLUDE)

# Αρχεία .o
OBJS = ipli.o parser.o interpreter.o $(LIB)/k08.a

# Το εκτελέσιμο πρόγραμμα
EXEC = ipli

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS = programs/nqueens.ipl

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Για να φτιάξουμε το k08.a, τρέχουμε το make στο lib directory.
$(LIB)/k08.a:
	$(MAKE) -C $(LIB) k08.a

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)