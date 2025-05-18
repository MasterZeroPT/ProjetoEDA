CC = gcc
CFLAGS = -Wall -Wextra -fPIC
AR = ar
ARFLAGS = rcs

LIBS = libfuncao.a libgrafos.a

all: funcao.o grafos.o main.o comp_libfuncao comp_libgrafos prog

funcao.o: ./src/funcao.c ./src/funcao.h
	gcc -c -fPIC ./src/funcao.c -o ./build/funcao.o

grafos.o: ./src/grafos.c ./src/grafos.h
	gcc -c -fPIC ./src/grafos.c -o ./build/grafos.o

main.o: ./src/main.c
	gcc -c ./src/main.c -o ./build/main.o

comp_libfuncao: ./build/funcao.o
	ar rcs ./build/libfuncao.a ./build/funcao.o

comp_libgrafos: ./build/grafos.o
	ar rcs ./build/libgrafos.a ./build/grafos.o

prog:
	gcc ./build/main.o -Lbuild -lfuncao -lgrafos -o ./prog

clean:
	rm ./build/*.o ./prog