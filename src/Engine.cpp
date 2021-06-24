#include "../include/Engine.hpp"
#include <cmath>
#include <vector>

using namespace std;

Engine::Engine(){
	reverse(pionBlackEval,pionWhiteEval);
	reverse(tourBlackEval,tourWhiteEval);
	reverse(kingBlackEval,kingWhiteEval);
	reverse(fouBlackEval,fouWhiteEval);
	// M = new Move(1);
}

void Engine::reverse(float BOARD1[8][8],float BOARD2[8][8]){
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			BOARD1[i][j] = BOARD2[7-i][7-j];
}

float Engine::getValueOfPiece(int BOARD[8][8],int i, int j){
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

float Engine::evaluateBoard(int BOARD[8][8]){
	float VALUE = 0;
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			if(BOARD[i][j] != 0)
				VALUE += getValueOfPiece(BOARD,i,j);
	return VALUE;
}

void Engine::print(int T[8][8]){
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
				if(T[i][j] >= 0)
					printf("   %d",T[i][j]);
				else
					printf("  %d",T[i][j]);
			}
			printf("\n");
		}
}


vector<vector<int>> Engine::gameMoves(int BOARD[8][8], int turn){

	vector<vector<int>> MOVES;
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(turn*BOARD[i][j] > 0){
				int from[2] = {i,j};
				M->getPossibilityOfMovment(MOVES,from,BOARD);
			}
		}
	}
	return MOVES;
}

vector<int> Engine::generateMovment(int BOARD[8][8]){
	vector<vector<int>> MOVES = gameMoves(BOARD,-1);
	vector<int> OPTIMALMOVE;
	OPTIMALMOVE.resize(4);
	float VAL = 9999, CURRENTVAL;

	for(int i=0; i<MOVES.size() ; i++){
		M->copyAndMove(MOVES[i][0],MOVES[i][1],MOVES[i][2],MOVES[i][3],BOARD);
		CURRENTVAL = evaluateBoard(M->VIRTUALBOARD);
		
		if(M->check(M->VIRTUALBOARD,1))
			CURRENTVAL -= 999999999999;
		if(CURRENTVAL < VAL){
			VAL = CURRENTVAL;
			OPTIMALMOVE[0] = MOVES[i][0];
			OPTIMALMOVE[1] = MOVES[i][1];
			OPTIMALMOVE[2] = MOVES[i][2];
			OPTIMALMOVE[3] = MOVES[i][3];
		}
	}
	return OPTIMALMOVE;
}

vector<int> Engine::minimaxRoot(int BOARD[8][8],float alpha, float beta, int depth){
	vector<vector<int>> MOVES = gameMoves(BOARD,-1);
	vector<int> OPTIMALMOVE;
	OPTIMALMOVE.resize(4);
	float VAL = 99999, CURRENTVAL;
	int VIRTUAL[8][8];
	for(int i=0; i<MOVES.size() ; i++){
		
		copy(VIRTUAL,BOARD);
		move(MOVES[i][0],MOVES[i][1],MOVES[i][2],MOVES[i][3],VIRTUAL);
		CURRENTVAL = minimax(VIRTUAL,alpha,beta,depth-1,1);
		
		if(CURRENTVAL < VAL){
			VAL = CURRENTVAL;
			OPTIMALMOVE[0] = MOVES[i][0];
			OPTIMALMOVE[1] = MOVES[i][1];
			OPTIMALMOVE[2] = MOVES[i][2];
			OPTIMALMOVE[3] = MOVES[i][3];
		}
	}

	return OPTIMALMOVE;
}

float Engine::minimax(int BOARD[8][8],float alpha, float beta, int depth, int turn){
	if(depth == 0){ //|| M->chek(BOARD,turn)
		return evaluateBoard(BOARD);
	}

	if(turn == 1){
		float CURRENTVAL = -9999;
		int VIRTUAL[8][8];
		vector<vector<int>> MOVES = gameMoves(BOARD,1);
		for(int i=0; i<MOVES.size() ; i++){
			copy(VIRTUAL,BOARD);
			move(MOVES[i][0],MOVES[i][1],MOVES[i][2],MOVES[i][3],VIRTUAL);
			CURRENTVAL = fmax(CURRENTVAL,minimax(VIRTUAL,alpha,beta,depth-1,-1));
			alpha = fmax(alpha,CURRENTVAL);
			if(beta <= alpha)
				return CURRENTVAL;
		}
		return CURRENTVAL;
	}
	else{
		float CURRENTVAL = 9999;
		int VIRTUAL[8][8];
		vector<vector<int>> MOVES = gameMoves(BOARD,-1);
		for(int i=0; i<MOVES.size() ; i++){
			copy(VIRTUAL,BOARD);
			move(MOVES[i][0],MOVES[i][1],MOVES[i][2],MOVES[i][3],VIRTUAL);
			CURRENTVAL = fmin(CURRENTVAL,minimax(VIRTUAL,alpha,beta,depth-1,1));
			beta = fmin(beta,CURRENTVAL);
			if(beta <= alpha)
				return CURRENTVAL;
		}
		return CURRENTVAL;
	}
}

void Engine::copy(int BOARD1[8][8], int BOARD2[8][8]){
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			BOARD1[i][j] = BOARD2[i][j];
}
void Engine::move(int xfrom, int yfrom, int xto, int yto, int BOARD[8][8]){
	int to[2] = {xto,yto}, from[2] = {xfrom,yfrom};
	M->move(from,to,BOARD);
}
