#include <render.h>
#include <stdio.h>
#include <counting.h>

#define DRAW_STR "DRAW!"
#define ZERO_STR "Noughts won"
#define CROSS_STR "Crosses won"

static int currentLine = 0;

static void repeat(const char* STR, size_t len){
	while (len-- && printf("%s", STR));
	fflush(stdout);
}

static void tableRows(char* sep, char* begin, char* middle, char* end, const size_t LEN){
	printf("%s", begin);
	for (size_t i = 0; i < LEN - 1; i++)
		printf("%s%s", sep, middle);
	printf("%s%s", sep, end);
	fflush(stdout);
}

static void elemBar(char* text, int number, const char* COLOR){
	printf("\u2502");
	if ( number != -1){
		printf("%s%s:", COLOR, text);
		repeat(" ", FIELD_SIZE_W - sizeStr(text) - sizeInt(number) - 3);
		printf("%d\e[0m", number);
	}
	else{
		repeat(" ", FIELD_SIZE_W / 2 - sizeStr(text) / 2 - 1);
		printf("%s%s\e[0m", COLOR, text);
		repeat(" ", FIELD_SIZE_W / 2 - sizeStr(text) / 2 - 1);
	}
	printf("\u2502\n");
	fflush(stdout);
}

void oncursor(){
	printf("\x1b[?25h");
	fflush(stdout);
}

void offcursor(){
	printf("\x1b[?25l");
	fflush(stdout);
}

void descentCursorEnd(){
	repeat("\x1b[B", currentLine);
	printf("\n");
	currentLine = 0;
	fflush(stdout);
}

void clear(const size_t LEN){
	for (size_t i = 0; i < LEN; i++){
		printf("\r\33[2K");
		if ( i + 1 < LEN)
		 	printf("\x1b[A");
	}
	fflush(stdout);
}

void printField(const int LEN){
	repeat(" ", FIELD_SIZE_W / 2 - (LEN * 2 + 1) / 2);
	tableRows("\u2500", "\u250C", "\u252C", "\u2510\n", LEN);
	for (size_t i = 0; i < LEN; i++){
		repeat(" ", FIELD_SIZE_W / 2 - (LEN * 2 + 1) / 2);
		tableRows(" ", "\u2502", "\u2502", "\u2502\n", LEN);
		repeat(" ", FIELD_SIZE_W / 2 - (LEN * 2 + 1) / 2);
		if (i + 1 != LEN)
			tableRows("\u2500", "\u251C", "\u253C", "\u2524\n", LEN);
	}
	tableRows("\u2500", "\u2514", "\u2534", "\u2518", LEN);
	printf("\r");
	repeat("\x1b[C", FIELD_SIZE_W / 2 - (LEN * 2 + 1) / 2 + 1);
	repeat("\x1b[A", LEN * 2 - 1);
	currentLine = LEN * 2 - 1;
	fflush(stdout);
}

void printBegin(const char* begin){
	repeat(" ", FIELD_SIZE_W / 2 - sizeStr(begin) / 2);
	printf("\e[1;36m%s\e[0m\n", begin);
	fflush(stdout);
}

void printBar(pairINT statistic){
	tableRows("\u2500", "\u250C", "\u2500", "\u2510\n", FIELD_SIZE_W / 2);
	elemBar("Score", -1,  "\e[38;5;208;1m");
	elemBar("Player", statistic.first, "\e[38;5;208;1m");
	elemBar("Computer", statistic.second, "\e[38;5;208;1m");
	tableRows("\u2500", "\u2514", "\u2500", "\u2518\n", FIELD_SIZE_W / 2);
	fflush(stdout);
}

void transferCursor(pairINT curr, pairINT newCurr){
	repeat(curr.first > newCurr.first ? "\x1b[A" : "\x1b[B", abs(curr.first - newCurr.first) * 2);
	repeat(curr.second > newCurr.second ? "\x1b[D" : "\x1b[C", abs(curr.second - newCurr.second) * 2);
	currentLine += (curr.first - newCurr.first) * 2;
	fflush(stdout);
}     	

void printValues(const int MOTION){
	if (!(MOTION % 2))
		printf("\e[1;34mX\e[0m\x1b[D");
	else
		printf("\e[38;5;113;1m0\e[0m\x1b[D");
	fflush(stdout);
}

void endParties(pairINT index, pairINT score, printWing value, const int LEN){
	transferCursor(index, makePairINT(LEN / 2, 0));
	printf("\r");
	switch (value){
		case DRAW:
			repeat("\x1b[C", FIELD_SIZE_W / 2 - sizeStr(DRAW_STR) / 2);
			printf("\e[1;33m%s\e[0m\r", DRAW_STR);
			break;
		case CROSS:
			repeat("\x1b[C", FIELD_SIZE_W / 2 - sizeStr(CROSS_STR) / 2);
			printf("\e[1;34m%s\e[0m\r", CROSS_STR);
			break;
		case ZERO:
			repeat("\x1b[C", FIELD_SIZE_W / 2 - sizeStr(ZERO_STR) / 2);
			printf("\e[1;32m%s\e[0m\r", ZERO_STR);
			break;
	}
	transferCursor(makePairINT(LEN / 2, 0), makePairINT(0, 0));
	currentLine += 1;
	printf("\x1b[A\x1b[A");
	repeat("\r\33[2K\x1b[A", 4);
	printBar(score);
	descentCursorEnd();
	fflush(stdout);
}

void button(char* left, char* right, bool selected){
	if (!selected)
		printf("\e[1;37;43m");
	printf("%s\e[0m", left);
	repeat(" ", FIELD_SIZE_W - sizeStr(left) - sizeStr(right));
	if (selected)
		printf("\e[1;37;43m");
	printf("%s\e[0m", right);
	fflush(stdout);
}	
