.PHONY: all, run, clean


all: main


main: main.o iostream.o work_field.o score.o bot.o
	gcc *.o -o Tic_tac_toe 


%.o: %.c
	gcc -c $< -o $*.o

clean:
	rm -f *.o Tic_tac_toe 

run:main
	./Tic_tac_toe
