# paths
MODULES = ../modules
INCLUDE = ../include

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)

# Για test coverage
CFLAGS += --coverage
LDFLAGS += --coverage

# Αρχεία .o
OBJS1 = stats_test.o $(MODULES)/stats.o
OBJS2 = stats_test.o $(MODULES)/stats_alt.o

# Το εκτελέσιμο πρόγραμμα
EXEC1 = stats_test
EXEC2 = stats_alt_test

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS1 =
ARGS2 =

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1)
	$(CC) $(OBJS1) -o $(EXEC1) $(LDFLAGS)

$(EXEC2): $(OBJS2)
	$(CC) $(OBJS2) -o $(EXEC2) $(LDFLAGS)

clean:
	rm -f $(OBJS1) $(OBJS2) $(EXEC1) $(EXEC2) *.gcda *.gcno
	rm -rf coverage

coverage: clean all run
	@mkdir -p coverage
	lcov --capture --directory=.. --output-file coverage/lcov.info
	cd coverage && genhtml lcov.info
	@echo "To see the report open the file below in your brower:"
	@echo "$$PWD/coverage/index.html"

valgrind: all
	valgrind ./$(EXEC1) -E $(ARGS1)
	valgrind ./$(EXEC2) -E $(ARGS2)

run: all
	./$(EXEC1) $(ARGS1)
	./$(EXEC2) $(ARGS2)