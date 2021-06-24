#include "../include/Evaluate.hpp"
#include <cmath>

Evaluate::Evaluate(){
	reverse(pionBlackEval,pionWhiteEval);
	reverse(tourBlackEval,tourWhiteEval);
	reverse(kingBlackEval,kingWhiteEval);
	reverse(fouBlackEval ,fouWhiteEval);
}

void Evaluate::reverse(float BOARD1[8][8],float BOARD2[8][8]){
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			BOARD1[i][j] = BOARD2[7-i][7-j];
}

float Evaluate::getValueOfPiece(int BOARD[8][8],int i, int j){
	int signe =  (BOARD[i][j] > 0)?1:-1;

	if     (abs(BOARD[i][j]) == 1){
		return   10*signe + ((BOARD[i][j] > 0)? pionWhiteEval[i][j] : -pionBlackEval[i][j]);
	}
	else if(abs(BOARD[i][j]) == 2){
		return   50*signe + ((BOARD[i][j] > 0)? tourWhiteEval[i][j] : -tourBlackEval[i][j]);
	}
	else if(abs(BOARD[i][j]) == 3){
		return  (30 + cavalierEval[i][j])*signe;
	}
	else if(abs(BOARD[i][j]) == 4){
		return   30*signe + ((BOARD[i][j] > 0)?  fouWhiteEval[i][j] : -fouBlackEval[i][j]);
	}
	else if(abs(BOARD[i][j]) == 5){
		return  (90 + dameEval[i][j])*signe;
	}
	else if(abs(BOARD[i][j]) == 6){
		return  900*signe + ((BOARD[i][j] > 0)? kingWhiteEval[i][j] : -kingBlackEval[i][j]);
	}
	else return 0;
}

float Evaluate::evaluateBoard(int BOARD[8][8]){
	float VALUE = 0;
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			if(BOARD[i][j] != 0)
				VALUE += getValueOfPiece(BOARD,i,j);
	return VALUE;
}