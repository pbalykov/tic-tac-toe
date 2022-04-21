.PHONY: run, all, clean


all: main


main: workField.o main.o pair.o render.o counting.o input.o endGame.o bot.o
	gcc $^ -o Tic-tac-toe 

%.o: %.c
	gcc -Iinclude -c $< -o $*.o

clean:
	rm -f *.o Tic-tac-toe

run:main
	./Tic-tac-toe

