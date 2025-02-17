# paths
LIB = ../../lib
INCLUDE = ../../include

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)

# Αρχεία .o
OBJS = iron_bank.o customer.o $(LIB)/k08.a
TEST_OBJS = customer_test.o customer.o $(LIB)/k08.a

# Το εκτελέσιμο πρόγραμμα
EXEC = iron_bank
TEST = customer_test

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS = 'Jon Snow'

all: $(EXEC) $(TEST)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

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