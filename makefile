CC = gcc

default: sizeof

sizeof: sizeof.c
	$(CC) sizeof.c -o ./bin/sizeof

clean:
	rm ./bin/*
