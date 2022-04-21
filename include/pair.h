#pragma once
#include <stdbool.h>

typedef struct{
	int first;
	int second;
}pairINT;

pairINT addPairINT(pairINT left, pairINT right);
pairINT makePairINT(int left, int right);
