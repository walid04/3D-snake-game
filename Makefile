CC = gcc 
CFLAGS = -Wall

all : snake

snake : snake.o main.o
	$(CC) $(CFLAGS) -o snake snake.o main.o -lglut -lGLU -lGL

snake.o : snake.c snake.h
	$(CC) $(CFLAGS) -o snake.o -c snake.c -lglut -lGLU -lGL

main.o : main.c snake.h
	$(CC) $(CFLAGS) -o main.o -c main.c -lglut -lGLU -lGL

clean :
	rm -f *.o *~ snake
