#include <signal.h>
#include <render.h>
#include <input.h>
#include <workField.h>
#include <bot.h>
#include <endGame.h>


int main(int argc, char* argv[]){

	signal(SIGINT, EXIT);
	sigset_t maskSiginit;
	sigemptyset(&maskSiginit);
	sigaddset(&maskSiginit, SIGINT);
	sigprocmask(SIG_BLOCK, &maskSiginit, NULL);
	const int LEN = 3;
	int** field = creatField(LEN);
	pairINT userIndex = {0, 0};
	pairINT score = {0, 0};
	int motion = 0;
	bool motionUser = 0;

	printBegin("Tic-tac-toe");
	printBar(score);
	printField(LEN);
	
	while(true){
		bool checkWing = checkEnd(field, LEN);
		if (checkWing || motion == LEN * LEN){
			if (checkWing)
				(!(motion % 2 == motionUser) ? score.first++ : score.second++);
			printWing wing = (checkWing ? (motion % 2 ? CROSS : ZERO) : DRAW);
			endParties(userIndex, score, wing, LEN);
			bool currsor = 0;
			if (score.first == 100000 || score.second == 100000){
				button("new game", "quit", currsor);
			}
			else{
				button("Reran", "exit", currsor);
			}
			offcursor();
			char event;
			do{
				sigprocmask(SIG_UNBLOCK, &maskSiginit, NULL);
				event = input();
				sigprocmask(SIG_BLOCK, &maskSiginit, NULL);
				if (event == 'D')
					currsor = (currsor + 1) % 2;
				else if (event == 'A')
					currsor = ((currsor - 1) % 2 + 2) % 2;
				clear(1);
				if (score.first == 100000 || score.second == 100000){
					button("new game", "quit", currsor);
				}
				else{
					button("Reran", "exit", currsor);
				}	
			}while(event != '\n');
			oncursor();
			if (!currsor){
				clearField(field, LEN);
				motion = 0;
				motionUser = (motionUser + 1) % 2;
				clear(LEN * 2 + 7); 
				userIndex = makePairINT(0, 0);
				printBar(score);
				printField(LEN);
				if (score.first == 100000 || score.second == 100000){
					score = makePairINT(0, 0);
					
				}
			}
			else{
				deleteField(field, LEN);
				EXIT(0);
			}
		}
		if (motion % 2 == motionUser){
			char event;
			do{
				sigprocmask(SIG_UNBLOCK, &maskSiginit, NULL);
				event = input();
				sigprocmask(SIG_BLOCK, &maskSiginit, NULL);
				pairINT tmpIndex = userIndex;
				if (event == 'W'){
					tmpIndex.first = ((tmpIndex.first - 1) % LEN + LEN) % LEN;
				}
				else if (event == 'S'){
					tmpIndex.first = (tmpIndex.first + 1) % LEN;
				}
				else if (event == 'A'){
					tmpIndex.second = ((tmpIndex.second - 1) % LEN + LEN) % LEN;
				}
				else if (event == 'D'){
					tmpIndex.second = (tmpIndex.second + 1) % LEN;
				}
				transferCursor(userIndex, tmpIndex);
				userIndex = tmpIndex;
			}while(event != '\n' || !setValues(field, userIndex, motion));
			printValues(motion++);
		}
		else{
			pairINT indexPc = pcMotion(field, LEN);
			setValues(field, indexPc, motion);
		       	transferCursor(userIndex, indexPc);
			printValues(motion++);
			transferCursor(indexPc, userIndex);
		}
	}
	return 0;
}
