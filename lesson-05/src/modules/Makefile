
CC=g++
FLAGS=-Wall -Wextra -Werror -std=c++20 -fmodules-ts

all: mexample.pcm main.o
	$(CC) $(FLAGS) mexample.pcm main.o -o main

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

mexample.pcm: mexample.cpp
	$(CC) $(FLAGS) -c mexample.cpp -o mexample.pcm

clean:
	rm -rf *.o *.pcm main gcm.cache
