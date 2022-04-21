#include <pair.h>

pairINT addPairINT(pairINT left, pairINT right){
	return (pairINT){left.first + right.first, left.second + right.second};
}

pairINT makePairINT(int left, int right){
	return (pairINT){left, right};
}
