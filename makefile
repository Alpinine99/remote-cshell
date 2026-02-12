CC = gcc

all: master slave
	@echo "up to date!"

master: master.c libformatter.a
	$(CC) master.c -L. -lformatter -o master -g

libformatter.a: formatter.o
	ar rcs libformatter.a formatter.o

formatter.o: formatter.c
	$(CC) -c formatter.c -o formatter.o

slave: slave.c libshell.a
	$(CC) slave.c -L. -lshell -o slave -g

libshell.a: shell.o
	ar rcs libshell.a shell.o

shell.o: shell.c
	$(CC) -c shell.c -o shell.o

clean:
	rm shell.o libshell.a master slave formatter.o libformatter.a

