CC=gcc
CFLAGS=-I

main: main.c plateauF.c
	gcc -o main main.c plateauF.c -I.