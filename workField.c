#include <workField.h>

int** creatField(const int LEN){
	int** field = malloc(sizeof(int*) * LEN);
	for (int i = 0; i < LEN; i++)
		field[i] = calloc(LEN, sizeof(int));
	return field;
}

void clearField(int** field, const int LEN){
	for (int i = 0; i < LEN; i++)
		for (int j = 0; j < LEN; j++)
			field[i][j] = 0;
}

void deleteField(int** field, const int LEN){
	for (int i = 0; i < LEN; i++)
		free(field[i]);
	free(field);
}

bool setValues(int** field, pairINT index, int motion){
	if (field[index.first][index.second])
		return false;
	field[index.first][index.second]= !(motion % 2) ? 1 : -1;
	return true;
}

bool checkEnd(int** field, const int LEN){
	pairINT diagonals = {0, 0};
	for (int i = 0; i < LEN; i++){
		pairINT columns = {0, 0};
		for (int j = 0; j < LEN; j++)
			columns = addPairINT(columns, makePairINT(field[i][j], field[j][i]));
		if (abs(columns.first) == LEN || abs(columns.second) == LEN)
			return true;
		diagonals = addPairINT(diagonals, makePairINT(field[i][i], field[i][LEN - 1 - i]));
	}
	if (abs(diagonals.first) == LEN || abs(diagonals.second) == LEN)
		return true;
	return false;
}
