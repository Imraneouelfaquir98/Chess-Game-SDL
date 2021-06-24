#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

#ifndef MOVE 
#define MOVE

class Move
{
public:
	Move(int TYPE);
	~Move();

	int*   getKingPosition        (int index, int BOARD[8][8]);
	void   setPieceType           (int TYPE);
	bool   isMovmentPossible      (int xFrom, int yFrom, int xTo, int yTo, int BOARD[8][8]);
	bool   areTheKingCheckedFor   (int xfrom, int yfrom, int xto, int yto, int BOARD[8][8], int index);
	void   copyAndMove            (int xfrom, int yfrom, int xto, int yto, int BOARD[8][8]);
	void   move                   (int * from, int * to, int BOARD[8][8]);
	bool   check                  (int BOARD[8][8], int index);
	void   addMovment             (vector<vector<int>> &U,int xfrom, int yfrom, int xto, int yto);
	bool   isThisSquareChecked    (int x, int y, int BOARD[8][8], int index);
	void   getPossibilityOfMovment(vector<vector<int>> &POSSIBLEMOVMENTS, int * from, int BOARD[8][8]);
	void   VerticalHorizontalMove (vector<vector<int>> &POSSIBLEMOVMENTS, int * from, int BOARD[8][8]);
	void   SegmentsMove           (vector<vector<int>> &POSSIBLEMOVMENTS, int * from, int BOARD[8][8]);

	int   pieceType = 1;
	int   VIRTUALBOARD[8][8];
};

#endif 
