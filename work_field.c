#include "work_field.h"


void creat_field(int*** data, const int len){
	*data =  malloc(sizeof(int*) * len);
	for (int i = 0; i < len; i++)
		(*data)[i]  = calloc(len, sizeof(int));
	return;	
}

void free_list(int** data, const int len){
	for (int i = 0; i < len; i++)
		free(data[i]);
	free(data);
	return;
}

bool placement(int** data, trio index){
	if (data[index.first][index.second])
		return 0;
	data[index.first][index.second] = index.third % 2 ? -1 : 1;
	return 1;
}        


bool check_victory(int** data, int len){
	pair diagonals = {0, 0};
	for (int i = 0; i < len; i++){
		pair columns = {0, 0};
		for (int j = 0; j < len; j++)
			columns = (pair){columns.first + data[i][j], columns.second + data[j][i]};
		if ((columns.first = abs(columns.first)) == 3 || (columns.second = abs(columns.second)) == 3)
			return true;
		diagonals = (pair){diagonals.first + data[i][i], diagonals.second + data[i][len - i - 1]};
	}
	if ((diagonals.first = abs(diagonals.first)) == 3 || (diagonals.second = abs(diagonals.second)) == 3)
		return true;
	return false;
}
