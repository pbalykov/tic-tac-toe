#pragma once
#include <stddef.h>
#include <pair.h>

#define FIELD_SIZE_W 17


typedef enum{
	DRAW,
	CROSS,
	ZERO,
}printWing;

typedef struct{
	int draw;
	int pc;
	int user;
}statistics;


void oncursor();
void offcursor();
void descentCursorEnd();
void clear(size_t len);
void printField(const int LEN);
void printBegin(const char* BEGIN);
void printBar(pairINT score);
void transferCursor(pairINT curr, pairINT newСurr);
void printValues(const int MOTION);
void endParties(pairINT index, pairINT score, printWing value, const int LEN);
void button(char* left, char* right, bool selected);
