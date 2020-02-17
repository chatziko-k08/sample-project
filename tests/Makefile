# paths
MODULES = ../modules
INCLUDE = ../include

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)

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
	gcc $(OBJS1) -o $(EXEC1)

$(EXEC2): $(OBJS2)
	gcc $(OBJS2) -o $(EXEC2)

clean:
	rm -f $(OBJS1) $(OBJS2) $(EXEC1) $(EXEC2)

run: all
	./$(EXEC1) $(ARGS1)
	./$(EXEC2) $(ARGS2)