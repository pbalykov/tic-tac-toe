#include "bot.h"

#include <stdio.h>

typedef struct{ 
	pair* arr;
	size_t len;
}list_pair;

void _free(void* data){
	if (data)
		free(data);
}


pair stroke(int** data, const int len){
	list_pair emp_cel = {NULL, 0};
	list_pair winning = {NULL, 0};
	list_pair loss = {NULL, 0};
	pair diagonal = {0, 0};
	pair_pair emptyDiag = {{0, 0}, {0, 0}};
	for (int i = 0; i < len; i++){
		pair columnsLine = {0, 0};
		pair_pair emptyColumnsLine = {{0, 0}, {0, 0}};
		for (int j = 0; j < len; j++){
			if (!data[i][j]){
				emp_cel.arr = realloc(emp_cel.arr, sizeof(pair) * ++emp_cel.len);
				emp_cel.arr[emp_cel.len - 1] = (pair){i, j};
				emptyColumnsLine.first = (pair){i, j};
			}
			if (!data[j][i])
				emptyColumnsLine.second = (pair){j, i};
			columnsLine = (pair){columnsLine.first + data[i][j], columnsLine.second + data[j][i]};
		}
		diagonal = (pair){diagonal.first + data[i][i], diagonal.second + data[len - i - 1][len - i - 1]};
		if (!data[i][i])
			emptyDiag.first = (pair){i, i};
		if (!data[len - i - 1][len - i - 1])
			emptyDiag.second = (pair){len - i - 1, len - i - 1};
		if (columnsLine.first == -2){
			winning.arr = realloc(winning.arr, sizeof(pair) * ++winning.len);
			winning.arr[winning.len - 1] = emptyColumnsLine.first;
		}
		if (columnsLine.first == 2){
			loss.arr = realloc(loss.arr, sizeof(pair) * ++loss.len);
			loss.arr[loss.len - 1] = emptyColumnsLine.first;
		}
		if (columnsLine.second == -2){
			winning.arr = realloc(winning.arr, sizeof(pair) * ++winning.len);
			winning.arr[winning.len - 1] = emptyColumnsLine.second;
		}
		if (columnsLine.second == 2){
			loss.arr = realloc(loss.arr, sizeof(pair) * ++loss.len);
			loss.arr[loss.len - 1] = emptyColumnsLine.second;
		}
	}
	if (diagonal.first == -2){
		winning.arr = realloc(winning.arr, sizeof(pair) * ++winning.len);
		winning.arr[winning.len - 1] = emptyDiag.first;
	}
	if (diagonal.first == 2){
		loss.arr = realloc(loss.arr, sizeof(pair) * ++loss.len);
		loss.arr[loss.len - 1] = emptyDiag.first;
	}
	if (diagonal.second == -2){
		winning.arr = realloc(winning.arr, sizeof(pair) * ++winning.len);
		winning.arr[winning.len - 1] = emptyDiag.second;
	}
	if (diagonal.second == 2){
		loss.arr = realloc(loss.arr, sizeof(pair) * ++loss.len);
		loss.arr[loss.len - 1] = emptyDiag.second;
	}
	pair ret = {-1, -1};
	if (winning.arr)
		ret = winning.arr[rand() % winning.len];
	else if (loss.arr)
		ret = loss.arr[rand() % loss.len];
	else if (emp_cel.arr)
		ret = emp_cel.arr[rand() % emp_cel.len];
	_free(loss.arr);
	_free(winning.arr);
	_free(emp_cel.arr);
	return ret;
}
