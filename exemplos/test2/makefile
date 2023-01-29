CFLAGS  =-g -Wall -Wextra -Werror -fsanitize=address
LDFLAGS =-fsanitize=address

all: main.o
	gcc $(LDFLAGS) main.o -o main
	./main 
main.o: main.c 
	gcc $(CFLAGS) -c main.c 

re: clean main

clean:
	rm -f *.o main 
