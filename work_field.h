#pragma once

#include "config.h"


void creat_field(int*** data, const int len);
void free_list(int** data, const int len);
bool placement(int**data,  trio index);
bool check_victory(int** data, int len);
