#include <sys/select.h>
#include <unistd.h>
#include <termios.h>
#include <input.h>


struct termios getcbreak(){
	struct termios values;
	tcgetattr(0, &values);
	return values;
}

void oncbreak(){
	struct termios values = getcbreak();
	values.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &values);
}

void offcbreak(){
	struct termios values = getcbreak();
	values.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &values);
}


char input(){
	oncbreak();
	char symbol;
	fd_set readFd, writeFd;
	FD_ZERO(&readFd);
	FD_ZERO(&writeFd);
	FD_SET(0, &readFd);
	struct timeval timeInter = {0, 5};
	read(0, &symbol, 1);
	if (symbol == 27){
		if (select(1, &readFd, &writeFd, &writeFd, &timeInter)){
			read(0, &symbol, 1);
			if (symbol == '['){
				read(0, &symbol, 1);
				if (symbol == 'A')
					symbol = 'W';
				else if (symbol == 'B')
					symbol = 'S';
				else if (symbol == 'C')
					symbol = 'D';
				else if (symbol == 'D')
					symbol = 'A';
			}
		}
	}
	offcbreak();
	return symbol;
}
