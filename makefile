CC = gcc
CFLAGS = -Wall -Wextra -fPIC
AR = ar
ARFLAGS = rcs

LIBS = libfuncao.a 

all: funcao.o main.o comp_lib prog

funcao.o: ./src/funcao.c ./src/funcao.h
	gcc -c -fPIC ./src/funcao.c -o ./build/funcao.o

main.o: ./src/main.c
	gcc -c ./src/main.c -o ./build/main.o

comp_lib: ./build/funcao.o 
	ar rcs ./build/libfuncao.a ./build/funcao.o 

prog:
	gcc ./build/main.o -Lbuild -lfuncao -o ./prog

clean:
	rm ./build/*.o ./prog