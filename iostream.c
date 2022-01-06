#include "iostream.h"


void repeat(const char* symbol, const int len){
	for (int i = 0; i < len; i++)
		printf("%s", symbol);
}


void cursor(pair index, pair index_tmp){
	int tmp_vertic = index_tmp.first - index.first, tmp_horiz = index_tmp.second - index.second;
	repeat(index_tmp.first > index.first ? "\x1b[B" : "\x1b[A", (tmp_vertic + tmp_vertic)  * (tmp_vertic > 0? 1 : -1));
	repeat(index_tmp.second > index.second ? "\x1b[C" : "\x1b[D", (tmp_horiz + tmp_horiz)  * (tmp_horiz > 0? 1 : -1));
}


void printField(const int len){
	for (int i = 0; i < len; i++){
		repeat(" ", LEN_AREA / 2 + LEN_AREA % 2  - (len + len + 1) / 2);
		repeat("+-", len);
		printf("+\n");
		repeat(" ", LEN_AREA / 2 + LEN_AREA % 2  - (len + len + 1) / 2);
		repeat("| ", len);
		printf("|\n");
	}
	repeat(" ", LEN_AREA / 2 + LEN_AREA % 2  - (len + len + 1) / 2);
	repeat("+-", len);
	printf("+\r\x1b[A");
	repeat("\x1b[C", LEN_AREA / 2 + LEN_AREA % 2  - (len + len + 1) / 2 + 1);
	cursor((pair){len - 1, 0}, (pair){0, 0}); 
}

void beginGame(){
	char* str = NAME_GAME;
	int len = _strlen(str);
	repeat(" ", LEN_AREA / 2 - len / 2);
	printf("\e[1;36m%s\n\e[0m", str);
}



void  WING_CROSS(){
	char* str = "Crosses won";
	int len = _strlen(str);
	repeat("\x1b[C", LEN_AREA / 2 + LEN_AREA % 2 - (len / 2));
	printf("\e[1;35m%s\e[0m\r", str);
}


void DRAW(){
	char* str = "Draw!";
	int len = _strlen(str);
	repeat("\x1b[C", LEN_AREA / 2 + LEN_AREA % 2 - len / 2 );
	printf("\e[38;5;208;1m%s\e[0m\r", str);
}

void WING_ZERO(){
	char* str = "Noughts won";
	int len = _strlen(str);
	repeat("\x1b[C", LEN_AREA / 2 + LEN_AREA % 2 - (len / 2));
	printf("\e[1;33m%s\e[0m\r", str);
}


void completions_game(pair index, int len, void(*function)()){
	cursor(index, (pair){len % 2, 0});
	printf("\r");
	function();
	repeat("\n", len % 2 + len % 2 + 2);
	printf("\e[1;31mClick to exit q, to continue click n\e[0m");
	printf("\x1b[?25l");
}



char input(){
	char znak;
	struct termios inp = {0}; 
	tcgetattr(0, &inp);
	inp.c_lflag &= ~ICANON;
	inp.c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW, &inp);
	znak = getchar();
	inp.c_lflag |= ICANON;
	inp.c_lflag |= ECHO;
	tcsetattr(0, TCSADRAIN, &inp);
	return znak;
}

