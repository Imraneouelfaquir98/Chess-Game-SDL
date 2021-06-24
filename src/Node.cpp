#include "../include/Node.hpp"

Node::Node(int turn){
	this->SCORE      = 0;
	this->nbrOfVisit = 0;
	this->turn       = turn;
}

double Node::getUCB1(){
	return (nbrOfVisit > 0)? SCORE/nbrOfVisit + 2*sqrt(log(PARENT->nbrOfVisit)/nbrOfVisit):999999;
}

void Node::copyBoard(int CURRENTBOARD[8][8]){
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			this->BOARD[i][j] = CURRENTBOARD[i][j];
}