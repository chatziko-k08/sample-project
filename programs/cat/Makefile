# paths
LIB = ../../lib
INCLUDE = ../../include

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)
LDFLAGS = -lm

# Αρχεία .o
OBJS = cat.o io.o $(LIB)/k08.a
TEST_OBJS = io_test.o io.o $(LIB)/k08.a

# Το εκτελέσιμο πρόγραμμα
EXEC = cat
TEST = io_test

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS = input-file

all: $(EXEC) $(TEST)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

$(TEST): $(TEST_OBJS)
	$(CC) $(TEST_OBJS) -o $(TEST) $(LDFLAGS)

# Για να φτιάξουμε το k08.a, τρέχουμε το make στο lib directory.
$(LIB)/k08.a:
	$(MAKE) -C $(LIB) k08.a

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(EXEC) $(TEST)

run: $(EXEC) $(TEST)
	./$(EXEC) $(ARGS)
	./$(TEST)
