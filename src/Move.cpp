#include "../include/Move.hpp"
#include <vector>
#include <cmath>

using namespace std;

Move::Move(int TYPE){
	pieceType = TYPE;
};

void Move::setPieceType(int TYPE){
	pieceType = TYPE;
}

bool Move::isMovmentPossible(int xFrom, int yFrom, int xTo, int yTo, int BOARD[8][8])
{
	if(abs(BOARD[xFrom][yFrom]) == 1 && fmax(xTo,yTo)<8  && fmin(xTo,yTo)>=0)
	{
		if (abs(xFrom - xTo) == 2 && yFrom == yTo)
		{
			int sgn = (xFrom-xTo>0)?1:-1;
			if((BOARD[xTo+sgn][yTo]==0) && (BOARD[xTo][yTo]==0))
				if( (xFrom==6 && BOARD[xFrom][yFrom]>0) || (xFrom==1 && BOARD[xFrom][yFrom]<0))
					return true;
		}
		else if(abs(xFrom - xTo) == 1)
		{	
			if ( yFrom == yTo  && BOARD[xTo][yTo] == 0)
			{
				if((xFrom>xTo && BOARD[xFrom][yFrom]>0) || (xFrom<xTo && BOARD[xFrom][yFrom]<0))
					return true;
			}
			else if(abs(yFrom - yTo)==1 && BOARD[xTo][yTo]*BOARD[xFrom][yFrom] < 0)
			{
				if((xFrom>xTo && BOARD[xFrom][yFrom]>0) || (xFrom<xTo && BOARD[xFrom][yFrom]<0))
					return true;
			}
		}
	}

	else if(abs(BOARD[xFrom][yFrom]) == 2 && fmax(xTo,yTo)<8  && fmin(xTo,yTo)>=0){
		if((xTo == xFrom) && (yTo != yFrom) && BOARD[xTo][yTo]*BOARD[xFrom][yFrom] <= 0)
		{
			int from = (yTo>yFrom)?yFrom:yTo, to = (yTo<yFrom)?yFrom:yTo;
			from++;
			while(from<to && BOARD[xTo][from] == 0)
				from++;
			if(from == to)
				return true;
		}

		else if((xTo != xFrom) && (yTo == yFrom) && BOARD[xTo][yTo]*BOARD[xFrom][yFrom] <= 0)
		{
			int from = (xTo>xFrom)?xFrom:xTo, to   = (xTo<xFrom)?xFrom:xTo;
			from++;
			while(from<to && BOARD[from][yTo] == 0)
				from++;
			if(from == to)
				return true;
		}
	}

	else if(abs(BOARD[xFrom][yFrom]) == 3 && fmax(xTo,yTo)<8  && fmin(xTo,yTo)>=0)
	{
		if( abs(xFrom - xTo) == 2 && abs(yFrom - yTo) == 1 && BOARD[xTo][yTo]*BOARD[xFrom][yFrom] <= 0)
			return true;
		else if( abs(xFrom - xTo) == 1 && abs(yFrom - yTo) == 2 && BOARD[xTo][yTo]*BOARD[xFrom][yFrom] <= 0)
			return true;
	}

	else if (abs(BOARD[xFrom][yFrom]) == 4 && fmax(xTo,yTo)<8  && fmin(xTo,yTo)>=0)
	{
		if((abs(xFrom - xTo) == abs(yFrom - yTo)) && BOARD[xTo][yTo]*BOARD[xFrom][yFrom] <= 0){

			if((xFrom<xTo && yFrom<yTo) || (xFrom>xTo && yFrom>yTo))
			{
				int ifrom = (xTo>xFrom)?xFrom:xTo, jfrom = (yTo>yFrom)?yFrom:yTo;
				int ito   = (xTo<xFrom)?xFrom:xTo, jto   = (yTo<yFrom)?yFrom:yTo;
				ifrom++; jfrom++;
				while( ifrom<ito && jfrom<jto && BOARD[ifrom][jfrom] == 0)
				{
					ifrom++; jfrom++;
				}
				if(ifrom == ito && jfrom == jto)
					return true;
			}
			else if((xFrom>xTo && yFrom<yTo) || (xFrom<xTo && yFrom>yTo))
			{
				int ifrom = (xTo<xFrom)?xFrom:xTo, jfrom = (yTo>yFrom)?yFrom:yTo;
				int ito   = (xTo>xFrom)?xFrom:xTo, jto   = (yTo<yFrom)?yFrom:yTo;
				ifrom--; jfrom++;
				while( ifrom>ito && jfrom<jto && BOARD[ifrom][jfrom] == 0)
				{
					ifrom--; jfrom++;
				}
				if(ifrom == ito && jfrom == jto)
					return true;
			}
		}
	}

	else if (abs(BOARD[xFrom][yFrom]) == 5 && fmax(xTo,yTo)<8  && fmin(xTo,yTo)>=0)
	{
		if((xTo == xFrom) && (yTo != yFrom) && BOARD[xTo][yTo]*BOARD[xFrom][yFrom] <= 0)
		{
			int from = (yTo>yFrom)?yFrom:yTo, to = (yTo<yFrom)?yFrom:yTo;
			from++;
			while(from<to && BOARD[xTo][from] == 0)
				from++;
			if(from == to)
				return true;
		}

		else if((xTo != xFrom) && (yTo == yFrom) && BOARD[xTo][yTo]*BOARD[xFrom][yFrom] <= 0)
		{
			int from = (xTo>xFrom)?xFrom:xTo, to   = (xTo<xFrom)?xFrom:xTo;
			from++;
			while(from<to && BOARD[from][yTo] == 0)
				from++;
			if(from == to)
				return true;
		}
		else if((abs(xFrom - xTo) == abs(yFrom - yTo)) && BOARD[xTo][yTo]*BOARD[xFrom][yFrom] <= 0)
		{
			if((xFrom<xTo && yFrom<yTo) || (xFrom>xTo && yFrom>yTo))
			{
				int ifrom = (xTo>xFrom)?xFrom:xTo, jfrom = (yTo>yFrom)?yFrom:yTo;
				int ito   = (xTo<xFrom)?xFrom:xTo, jto   = (yTo<yFrom)?yFrom:yTo;
				ifrom++; jfrom++;
				while( ifrom<ito && jfrom<jto && BOARD[ifrom][jfrom] == 0)
				{
					ifrom++; jfrom++;
				}
				if(ifrom == ito && jfrom == jto)
					return true;
			}
			else if((xFrom>xTo && yFrom<yTo) || (xFrom<xTo && yFrom>yTo))
			{
				int ifrom = (xTo<xFrom)?xFrom:xTo, jfrom = (yTo>yFrom)?yFrom:yTo;
				int ito   = (xTo>xFrom)?xFrom:xTo, jto   = (yTo<yFrom)?yFrom:yTo;
				ifrom--; jfrom++;
				while( ifrom>ito && jfrom<jto && BOARD[ifrom][jfrom] == 0)
				{
					ifrom--; jfrom++;
				}
				if(ifrom == ito && jfrom == jto)
					return true;
			}
		}
	}

	else if (abs(BOARD[xFrom][yFrom]) == 6 && fmax(xTo,yTo)<8  && fmin(xTo,yTo)>=0)
	{
		if((abs(xFrom-xTo) <= 1 && abs(yFrom-yTo) <= 1) && BOARD[xTo][yTo]*BOARD[xFrom][yFrom] <= 0){
			if(xFrom != xTo || yFrom != yTo)
				return true;
		}
		if(abs(yFrom-yTo) == 2 && (xTo == 0 || xTo == 7) && BOARD[xTo][yTo] == 0)
		{
			if(abs(BOARD[xTo][7]) == 2 && (yTo == 6 || yTo == 5)){
				if(yTo == 6 && BOARD[xTo][yTo-1] == 0 && pieceType == 1)
					return true;
				else if(yTo == 5 && BOARD[xTo][yTo-1] == 0 && BOARD[xTo][yTo+1] == 0 && pieceType == -1)
					return true;
			}
			else if(abs(BOARD[xTo][0]) == 2 && (yTo == 2 || yTo == 1)){
				if(yTo == 2 && BOARD[xTo][yTo-1] == 0 && BOARD[xTo][yTo+1] == 0 && pieceType == 1)
					return true;
				else if(yTo == 1 && BOARD[xTo][yTo+1] == 0 && pieceType == -1)
					return true;
			}
		}

	}
	return false;
}

bool Move::areTheKingCheckedFor(int xfrom, int yfrom, int xto, int yto, int BOARD[8][8], int index){

	copyAndMove(xfrom,yfrom,xto,yto,BOARD);
	int* pos = getKingPosition(index,VIRTUALBOARD);
	for(int j=0 ; j<8 ; j++){
		for(int i=0 ; i<8 ; i++){
			if(index*VIRTUALBOARD[i][j] < 0){
				if(isMovmentPossible(i,j,pos[0],pos[1],VIRTUALBOARD))
					return true;
			}
		}
	}
	return false;
}

int* Move::getKingPosition(int index, int BOARD[8][8]){
	int* POSITION = (int*)malloc(sizeof(int)*2);
	for(int i = 0; i<8; i++)
		for(int j = 0; j<8; j++)
			if(index*BOARD[i][j] == 6){
				POSITION[0] = i;
				POSITION[1] = j;
			}
	return POSITION;
}

void Move::copyAndMove(int xfrom, int yfrom, int xto, int yto, int BOARD[8][8]){
	for(int i=0 ; i<8 ; i++)
		for(int j=0 ; j<8 ; j++)
			VIRTUALBOARD[i][j] = BOARD[i][j];
	int to[2] = {xto,yto}, from[2] = {xfrom,yfrom};
	move(from,to,VIRTUALBOARD);
}

void Move::move(int * from, int * to, int BOARD[8][8])
{
	if(abs(BOARD[from[0]][from[1]])==6 && abs(from[1]-to[1]) == 2)
	{
		if(to[1] == 6)
		{
			BOARD[to  [0]][to  [1]]   = BOARD[from[0]][from[1]];
			BOARD[from[0]][from[1]+1] = BOARD[to[0]][to[1]+1];
			BOARD[to  [0]][to  [1]+1] = 0;
			BOARD[from[0]][from[1]]   = 0;
		}
		else if(to[1] == 2)
		{
			BOARD[to  [0]][to  [1]]   = BOARD[from[0]][from[1]];
			BOARD[from[0]][from[1]-1] = BOARD[to[0]][to[1]-2];
			BOARD[to  [0]][to  [1]-2] = 0;
			BOARD[from[0]][from[1]]   = 0;
		}
		else if(to[1] == 5)
		{
			BOARD[to[0]][to[1]]     = BOARD[from[0]][from[1]];
			BOARD[to[0]][to[1]-1]   = BOARD[to[0]][to[1]+2];
			BOARD[to[0]][to[1]+2]   = 0;
			BOARD[from[0]][from[1]] = 0;
		}
		else if(to[1] == 1)
		{
			BOARD[to  [0]][to  [1]]   = BOARD[from[0]][from[1]];
			BOARD[from[0]][from[1]-1] = BOARD[to  [0]][to  [1]-1];
			BOARD[to  [0]][to  [1]-1] = 0;
			BOARD[from[0]][from[1]]   = 0;
		}
	}
	else if(abs(BOARD[from[0]][from[1]]) == 1 ){
		if(to[0] == 0 && BOARD[from[0]][from[1]] == 1)
			BOARD[from[0]][from[1]] = 5;
		else if(to[0] == 7 && BOARD[from[0]][from[1]] == -1)
			BOARD[from[0]][from[1]] = -5;
		
		BOARD[to[0]][to[1]] = BOARD[from[0]][from[1]];
		BOARD[from[0]][from[1]] = 0;
	}
	else{
		BOARD[to  [0]][to  [1]] = BOARD[from[0]][from[1]];
		BOARD[from[0]][from[1]] = 0;
	}
}

void Move::getPossibilityOfMovment(vector<vector<int>> &POSSIBLEMOVMENTS, int * from, int BOARD[8][8]){

	// vector<vector<int>> POSSIBLEMOVMENTS;// (1 , vector<int>(4,0));

	int signe = BOARD[from[0]][from[1]]/abs(BOARD[from[0]][from[1]]);
	if(abs(BOARD[from[0]][from[1]]) == 1)
	{
		if(BOARD[from[0]-signe][from[1]] == 0 && !areTheKingCheckedFor(from[0],from[1],from[0]-signe,from[1],BOARD,signe))	
		{	
			addMovment(POSSIBLEMOVMENTS,from[0],from[1],from[0]-signe,from[1]);
		}
		if((from[0]*signe == -1 || from[0]*signe == 6) && BOARD[from[0]-2*signe][from[1]] == 0 && BOARD[from[0]-signe][from[1]] == 0  && !areTheKingCheckedFor(from[0],from[1],from[0]-2*signe,from[1],BOARD,signe))
		{
			addMovment(POSSIBLEMOVMENTS,from[0],from[1],from[0]-2*signe,from[1]);
		}
		if (BOARD[from[0]-signe][from[1]-signe]*BOARD[from[0]][from[1]] < 0 && !areTheKingCheckedFor(from[0],from[1],from[0]-signe,from[1]-signe,BOARD,signe))
		{
			if(fmax(from[0]-signe,from[1]-signe) < 8 && fmin(from[0]-signe,from[1]-signe) >=0 )
				addMovment(POSSIBLEMOVMENTS,from[0],from[1],from[0]-signe,from[1]-signe);
		}
		if (BOARD[from[0]-signe][from[1]+signe]*BOARD[from[0]][from[1]] < 0 && !areTheKingCheckedFor(from[0],from[1],from[0]-signe,from[1]+signe,BOARD,signe))
		{
			if(fmax(from[0]-signe,from[1]+signe) < 8 && fmin(from[0]-signe,from[1]+signe) >=0 )
				addMovment(POSSIBLEMOVMENTS,from[0],from[1],from[0]-signe,from[1]+signe);
		}
		// else if(from[0]*signe != -1 || from[0]*signe != 6){
		// 	for(int i=0;i<3;i++)
		// 		if(isMovmentPossible(from[0],from[1],from[0]-signe,from[1]-1+i,BOARD) && !areTheKingCheckedFor(from[0],from[1],from[0]-signe,from[1]-1+i,BOARD,signe))
		// 			addMovment(POSSIBLEMOVMENTS,from[0],from[1],from[0]-signe,from[1]-1+i);
		// }
	}

	else if(abs(BOARD[from[0]][from[1]]) == 2)
		VerticalHorizontalMove(POSSIBLEMOVMENTS,from,BOARD);

	else if(abs(BOARD[from[0]][from[1]]) == 3){
		for(int j=fmax(from[1]-2,0) ; j<fmin(from[1]+3,8) ; j++){
			for(int i=fmax(from[0]-2,0) ; i<fmin(from[0]+3,8) ; i++){
				if     (abs(from[0]-i)==2 && abs(from[1]-j)==1 && signe*BOARD[i][j] <= 0 && !areTheKingCheckedFor(from[0],from[1],i,j,BOARD,signe)){
					addMovment(POSSIBLEMOVMENTS,from[0],from[1],i,j);
				}
				else if(abs(from[0]-i)==1 && abs(from[1]-j)==2 && signe*BOARD[i][j] <= 0 && !areTheKingCheckedFor(from[0],from[1],i,j,BOARD,signe)){
					addMovment(POSSIBLEMOVMENTS,from[0],from[1],i,j);
				}
			}
		}
	}

	else if(abs(BOARD[from[0]][from[1]]) == 4)
		SegmentsMove(POSSIBLEMOVMENTS,from,BOARD);
	
	else if(abs(BOARD[from[0]][from[1]]) == 5)
	{
		VerticalHorizontalMove(POSSIBLEMOVMENTS,from,BOARD);
		SegmentsMove(POSSIBLEMOVMENTS,from,BOARD);
	}
	else if(abs(BOARD[from[0]][from[1]]) == 6){
		for(int j=from[1]-1 ; j<from[1]+2 ; j++){
			for(int i=from[0]-1 ; i<from[0]+2 ; i++){
				int to[2] = {i,j};
				if(fmax(i,j)<8 && fmin(i,j)>=0 && signe*BOARD[i][j] <= 0 && !isThisSquareChecked(i,j,BOARD,signe))
					addMovment(POSSIBLEMOVMENTS,from[0],from[1],i,j);
			}
		}
		if(from[0]==7){
			for(int i=1; i<7 ; i++)
				if(isMovmentPossible(from[0],from[1],7,i,BOARD) && !isThisSquareChecked(7,i,BOARD,signe))
					addMovment(POSSIBLEMOVMENTS,from[0],from[1],7,i);
		}
		else if(from[0]==0){
			for(int i=1; i<7 ; i++)
				if(isMovmentPossible(from[0],from[1],0,i,BOARD) && !isThisSquareChecked(0,i,BOARD,signe))
					addMovment(POSSIBLEMOVMENTS,from[0],from[1],0,i);
		}
	}
}

void Move::addMovment(vector<vector<int>> &U,int xfrom, int yfrom, int xto, int yto){
	vector<int> V;
	V.push_back(xfrom);
	V.push_back(yfrom);
	V.push_back(xto);
	V.push_back(yto);

	U.push_back(V);
}

bool Move::isThisSquareChecked(int x, int y, int BOARD[8][8], int index){
	
	int* positionKing = getKingPosition(index,BOARD);
	
	copyAndMove(positionKing[0],positionKing[1],x,y,BOARD);
	for(int j=0 ; j<8 ; j++){
		for(int i=0 ; i<8 ; i++){
			if(index*VIRTUALBOARD[i][j] < 0){
				if(isMovmentPossible(i,j,x,y,VIRTUALBOARD))
					return true;
			}
		}
	}
	return false;
}

void   Move::VerticalHorizontalMove (vector<vector<int>> &POSSIBLEMOVMENTS, int * from, int BOARD[8][8]){
	int signe = BOARD[from[0]][from[1]]/abs(BOARD[from[0]][from[1]]);
	int i = from[0]+1, j = from[1]+1;
	while(i<=7 && signe*BOARD[i][from[1]] <= 0){
		if(!areTheKingCheckedFor(from[0],from[1],i,from[1],BOARD,signe))
			addMovment(POSSIBLEMOVMENTS,from[0],from[1],i,from[1]);
		if(signe*BOARD[i][from[1]] < 0)
			break;
		i++;
	}
	while(j<=7 && signe*BOARD[from[0]][j] <= 0){
		if(!areTheKingCheckedFor(from[0],from[1],from[0],j,BOARD,signe))
			addMovment(POSSIBLEMOVMENTS,from[0],from[1],from[0],j);
		if(signe*BOARD[from[0]][j] < 0)
			break;
		j++;
	}
	i = from[0]-1;
	while(i>=0 && signe*BOARD[i][from[1]] <= 0){
		if(!areTheKingCheckedFor(from[0],from[1],i,from[1],BOARD,signe))
			addMovment(POSSIBLEMOVMENTS,from[0],from[1],i,from[1]);
		if(signe*BOARD[i][from[1]] < 0)
			break;
		i--;
	}
	j= from[1]-1;
	while(j>=0 && signe*BOARD[from[0]][j] <= 0){
		if(!areTheKingCheckedFor(from[0],from[1],from[0],j,BOARD,signe))
			addMovment(POSSIBLEMOVMENTS,from[0],from[1],from[0],j);
		if(signe*BOARD[from[0]][j] < 0)
			break;
		j--;
	}
}

void   Move::SegmentsMove(vector<vector<int>> &POSSIBLEMOVMENTS, int * from, int BOARD[8][8]){
	int signe = BOARD[from[0]][from[1]]/abs(BOARD[from[0]][from[1]]);
	int i = from[0]+1, j = from[1]+1;
		while(i<=7 && j<=7 && signe*BOARD[i][j] <= 0){
			if(!areTheKingCheckedFor(from[0],from[1],i,j,BOARD,signe))
				addMovment(POSSIBLEMOVMENTS,from[0],from[1],i,j);
			if(signe*BOARD[i][j] < 0)
				break;
			i++; j++;
		}

		i = from[0]-1, j = from[1]-1;
		while(i>=0 && j>=0 && signe*BOARD[i][j] <= 0){
			if(!areTheKingCheckedFor(from[0],from[1],i,j,BOARD,signe))
				addMovment(POSSIBLEMOVMENTS,from[0],from[1],i,j);
			if(signe*BOARD[i][j] < 0)
				break;
			i--; j--;
		}

		i = from[0]-1, j = from[1]+1;
		while(i>=0 && j<=7 && signe*BOARD[i][j] <= 0){
			if(!areTheKingCheckedFor(from[0],from[1],i,j,BOARD,signe))
				addMovment(POSSIBLEMOVMENTS,from[0],from[1],i,j);
			if(signe*BOARD[i][j] < 0)
				break;
			i--; j++;
		}

		i = from[0]+1, j = from[1]-1;
		while(i<=7 && j>=0 && signe*BOARD[i][j] <= 0){
			if(!areTheKingCheckedFor(from[0],from[1],i,j,BOARD,signe))
				addMovment(POSSIBLEMOVMENTS,from[0],from[1],i,j);
			if(signe*BOARD[i][j] < 0)
				break;
			i++; j--;
		}
}

bool Move::check(int BOARD[8][8], int index){
	vector<vector<int>> MOVEMENTS;
	for(int i=0; i<8; i++){
		for(int j=0; j<8 ; j++){
			if(index*BOARD[i][j] > 0){
				int from[2] = {i,j};
				getPossibilityOfMovment(MOVEMENTS,from,BOARD);
				if(MOVEMENTS.size() > 0)
					return false;
			}
		}
	}
	return true;
}