# options
CC = gcc
CFLAGS = -Wall -g 

# Αρχεία .o
OBJS = examples.o

# Το εκτελέσιμο πρόγραμμα
EXEC = examples

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS =

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)
