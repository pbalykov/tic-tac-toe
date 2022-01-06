#include "work_field.h"
#include "iostream.h"
#include "bot.h"



int main(){
	srand(time(NULL));
	const int len = 3;
	int** data = NULL;
	int shag = 0;
       	beginGame();
	creat_field(&data, len);
	printField(len);
	pair index = {0, 0};
	while (1){
		bool wing = check_victory(data, len);
		if ( wing || shag == 9){ 
			 completions_game(index, len, (wing ? ( shag % 2 ? WING_CROSS : WING_ZERO) : DRAW));
			 char symbol;
			 do{
				 symbol = input();
		 	 }while(symbol != 'n' && symbol != 'q');
			 if (symbol == 'q')
				 break;
			 printf("\x1b[?25h");
			 repeat("\r\33[2K\x1b[A", len + len + 1);
			 index = (pair){0, 0};
			 shag = 0;
			 free_list(data, len);
			 creat_field(&data, len);
		         printField(len);

		}
		if (shag % 2){
			pair tmp_index = stroke(data, len);
		        placement(data, (trio){tmp_index.first, tmp_index.second, shag});
			cursor(index, tmp_index);
			printf("%s", ((!(shag++ % 2) ? CROSS : ZERO)));
			cursor(tmp_index, index);
		}
		else{
			char symbol;
			do{
				symbol = input();
				if (symbol == 'W' || symbol == 'w'){
					pair tmp_index = {((index.first - 1) % len + len) % len, index.second};
					cursor(index, tmp_index);
					index = tmp_index;
				}
				else if (symbol == 'S' || symbol == 's'){
					pair tmp_index = {((index.first + 1) % len + len) % len, index.second};
					cursor(index, tmp_index);
					index = tmp_index;
				}
				else if (symbol == 'D' || symbol == 'd'){
					pair tmp_index = {index.first, ((index.second + 1) % len + len) % len};
					cursor(index, tmp_index);
					index = tmp_index;
				}
				else if (symbol == 'A' || symbol == 'a'){
					pair tmp_index = {index.first, ((index.second - 1) % len + len) % len};
					cursor(index, tmp_index);
					index = tmp_index;
				}
			}
			while (symbol != '\n' || !(placement(data, (trio){index.first, index.second, shag})));
			printf("%s", ((!(shag++ % 2) ? CROSS : ZERO)));
		}
	}
	printf("\n\x1b[?25h");
	free_list(data, len);
	return 0;
}
	

