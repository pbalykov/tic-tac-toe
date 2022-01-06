#include "score.h"



int abs(const int a){
	return a > 0 ? a : a * -1;
}

int _strlen(char* string){
	char* string1 = string;
	while(*string++);
	return string - string1 - 1;
}

