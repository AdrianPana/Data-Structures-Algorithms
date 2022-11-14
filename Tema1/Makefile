CC=gcc

build: tema1

tema1: tema1.c list.c procedures.c
	$(CC) tema1.c list.c procedures.c -o tema1 -lm

tema1.o: tema1.c
	$(CC) -c tema1.c

list.o: list.c
	$(CC) -c list.c

procedures.o: procedures.c
	$(CC) -c procedures.c

clean: 
	rm -rf tema1 *.o

run: tema1
	./tema1