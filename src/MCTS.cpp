#include "../include/MCTS.hpp"

using namespace std;

MCTS::MCTS(){
	// HEAD = new Node();
}

Node * MCTS::makeChildren(Node ** NODE){
	vector<vector<int>> ACTIONS = getActions ((*NODE)->BOARD,(*NODE)->turn);
	for(int i=0; i<ACTIONS.size(); i++){
		Node *N = new Node(-(*NODE)->turn);
		N->ACTION = ACTIONS[i];
		N->PARENT = *NODE;

		N->copyBoard((*NODE)->BOARD);
		int from[2] = {ACTIONS[i][0], ACTIONS[i][1]}, to[2] = {ACTIONS[i][2], ACTIONS[i][3]}; 
		M->move(from, to, N->BOARD);

		N->SCORE = -EVAL->evaluateBoard(N->BOARD);
		if(M->check(N->BOARD,N->turn))
			N->SCORE += N->turn*999999;
		N->nbrOfVisit += 1;

		Node *tmp = N;
		do{
			tmp->PARENT->SCORE += tmp->SCORE;
			tmp->PARENT->nbrOfVisit += 1;
			tmp = tmp->PARENT;
		}while(tmp != HEAD);

		(*NODE)->CHILDRENS.push_back(N);
	}
	return HEAD;
}

vector<vector<int>> MCTS::getActions (int BOARD[8][8], int turn){
	vector<vector<int>> ACTIONS;
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(turn*BOARD[i][j] > 0){
				int from[2] = {i,j};
				M->getPossibilityOfMovment(ACTIONS,from,BOARD);
			}
		}
	}
	return ACTIONS;
}


Node * MCTS::getTheBestAction (){
	Node * CURRENT_NODE = HEAD->CHILDRENS[0];
	for(int i=1; i<HEAD->CHILDRENS.size(); i++){
		if(CURRENT_NODE->SCORE < HEAD->CHILDRENS[i]->SCORE)
			CURRENT_NODE = HEAD->CHILDRENS[i];
	}
	return CURRENT_NODE;
}

Node * MCTS::setHead(int xfrom, int yfrom, int xto, int yto){
	for(int i=0; i<HEAD->CHILDRENS.size(); i++){
		vector<int> A = HEAD->CHILDRENS[i]->ACTION;
		if(A[0] == xfrom && A[1] == yfrom && A[2] == xto && A[3] == yto){
			HEAD = HEAD->CHILDRENS[i];
			return HEAD;
		}
	}
	HEAD = new Node(-HEAD->turn);
	return HEAD;
}

Node ** MCTS::getCurrentNode(){
	if(HEAD->nbrOfVisit <= 1)
		return &HEAD;
	else{
		Node ** CURRENT_HEAD = &HEAD;
		Node ** CURRENT_NODE = &((*CURRENT_HEAD)->CHILDRENS[0]);
		double CURRENT_UCB1 = (*CURRENT_NODE)->getUCB1();
		while((*CURRENT_HEAD)->nbrOfVisit > 1){
			for(int i=0; i<(*CURRENT_HEAD)->CHILDRENS.size(); i++){
				if(CURRENT_UCB1  <   (*CURRENT_HEAD)->CHILDRENS[i]->getUCB1()){
					CURRENT_NODE = &((*CURRENT_HEAD)->CHILDRENS[i]);
					CURRENT_UCB1 =   (*CURRENT_NODE)->getUCB1();
				}
			}
			if((*CURRENT_NODE)->nbrOfVisit <=1 )
				return CURRENT_NODE;
			else{
				CURRENT_HEAD  =  CURRENT_NODE;
				CURRENT_NODE  = &((*CURRENT_HEAD)->CHILDRENS[0]);
				CURRENT_UCB1  = (*CURRENT_NODE)->getUCB1();
			}
		}
		return CURRENT_NODE;
	}
}

Node* MCTS::doIterations(int TIME){
	for(int i=0; i<TIME; i++){
		HEAD = makeChildren(getCurrentNode());
	}
	return HEAD;
}



void MCTS::print(int T[8][8]){
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
