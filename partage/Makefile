#THIEL Samantha, COZZOLINO Christine, M1 Informatique - Projet Réseaux

CC = gcc
CCFLAGS = -w -Wall -g

OBJ = iftun.o

all : test_iftun

test_iftun: test_iftun.c iftun.o
	$(CC) $(CCFLAGS) test_iftun.c -o test_iftun iftun.o


iftun.o : iftun.c
	$(CC) $(CCFLAGS) -c iftun.c


clean:
	- rm *.o
	- rm test_iftun

