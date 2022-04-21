#include <bot.h>
#include <stdlib.h>
#include <time.h>

typedef struct{ 
	pairINT* arr;
	size_t len;
}list_pair;

typedef struct{
	pairINT first;
	pairINT second;
}pairINT_pairINT;

pairINT pcMotion(int** field, const int LEN){
	srand(time(NULL));
	list_pair emp_cel = {NULL, 0};
	list_pair winning = {NULL, 0};
	list_pair loss = {NULL, 0};
	pairINT diagonal = {0, 0};
	pairINT_pairINT emptyDiag = {{0, 0}, {0, 0}};
	for (int i = 0; i < LEN; i++){
		pairINT columnsLine = {0, 0};
		pairINT_pairINT emptyColumnsLine = {{0, 0}, {0, 0}};
		for (int j = 0; j < LEN; j++){
			if (!field[i][j]){
				emp_cel.arr = realloc(emp_cel.arr, sizeof(pairINT) * ++emp_cel.len);
				emp_cel.arr[emp_cel.len - 1] = (pairINT){i, j};
				emptyColumnsLine.first = (pairINT){i, j};
			}
			if (!field[j][i])
				emptyColumnsLine.second = (pairINT){j, i};
			columnsLine = (pairINT){columnsLine.first + field[i][j], columnsLine.second + field[j][i]};
		}
		diagonal = (pairINT){diagonal.first + field[i][i], diagonal.second + field[LEN - i - 1][LEN - i - 1]};
		if (!field[i][i])
			emptyDiag.first = (pairINT){i, i};
		if (!field[LEN - i - 1][LEN - i - 1])
			emptyDiag.second = (pairINT){LEN - i - 1, LEN - i - 1};
		if (columnsLine.first == -2){
			winning.arr = realloc(winning.arr, sizeof(pairINT) * ++winning.len);
			winning.arr[winning.len - 1] = emptyColumnsLine.first;
		}
		if (columnsLine.first == 2){
			loss.arr = realloc(loss.arr, sizeof(pairINT) * ++loss.len);
			loss.arr[loss.len - 1] = emptyColumnsLine.first;
		}
		if (columnsLine.second == -2){
			winning.arr = realloc(winning.arr, sizeof(pairINT) * ++winning.len);
			winning.arr[winning.len - 1] = emptyColumnsLine.second;
		}
		if (columnsLine.second == 2){
			loss.arr = realloc(loss.arr, sizeof(pairINT) * ++loss.len);
			loss.arr[loss.len - 1] = emptyColumnsLine.second;
		}
	}
	if (diagonal.first == -2){
		winning.arr = realloc(winning.arr, sizeof(pairINT) * ++winning.len);
		winning.arr[winning.len - 1] = emptyDiag.first;
	}
	if (diagonal.first == 2){
		loss.arr = realloc(loss.arr, sizeof(pairINT) * ++loss.len);
		loss.arr[loss.len - 1] = emptyDiag.first;
	}
	if (diagonal.second == -2){
		winning.arr = realloc(winning.arr, sizeof(pairINT) * ++winning.len);
		winning.arr[winning.len - 1] = emptyDiag.second;
	}
	if (diagonal.second == 2){
		loss.arr = realloc(loss.arr, sizeof(pairINT) * ++loss.len);
		loss.arr[loss.len - 1] = emptyDiag.second;
	}
	pairINT ret = {-1, -1};
	if (winning.arr)
		ret = winning.arr[rand() % winning.len];
	else if (loss.arr)
		ret = loss.arr[rand() % loss.len];
	else if (emp_cel.arr)
		ret = emp_cel.arr[rand() % emp_cel.len];
	free(loss.arr);
	free(winning.arr);
	free(emp_cel.arr);
	return ret;
}
