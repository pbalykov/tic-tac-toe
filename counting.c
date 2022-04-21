#include <counting.h>

size_t sizeInt(int numder){
	size_t k = 0;
	while (++k && (numder = numder / 10));
	return k;
}

size_t sizeStr(const char* STR){
	const char* TMP = STR;
	while (*TMP++);
	return TMP - STR - 1;
}

int abs(const int OTHER){
	return OTHER > 0 ? OTHER : -OTHER;
}
