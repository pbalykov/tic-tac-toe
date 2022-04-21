#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <pair.h>


int** creatField(const int LEN);
void clearField(int** field, const int LEN);
void deleteField(int** field, const int LEN);
bool setValues(int** field, pairINT index, int motion);
bool checkEnd(int** field, const int LEN);
