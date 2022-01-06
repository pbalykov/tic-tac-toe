#pragma once

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "config.h"


#define CROSS "\e[1;34mX\e[0m\x1b[D"
#define ZERO  "\e[38;5;113;1m0\e[0m\x1b[D"

#define NAME_GAME "Game Tic tac toe"
#define LEN_AREA 30


void WING_CROSS();
void WING_ZERO(); 
void DRAW();

void repeat(const char* symbol, const int len);
void beginGame();
char input();
void printField(const int len);
void cursor(pair index, pair index_tmp);
void completions_game(pair index, int len, void (*wing)());
