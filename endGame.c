#include <endGame.h>
#include <input.h>
#include <render.h>
#include <stdlib.h>
#include <stdio.h>

void EXIT(const int OTHER){
	offcbreak();
	oncursor();
	descentCursorEnd();
	exit(OTHER);
}
