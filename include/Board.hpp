#include <iostream>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
// #include "../include/Move.hpp"
#include "../include/Engine.hpp"
#include "../include/MCTS.hpp"


class Board
{
public:

	Board(int TYPE);
	~Board();

	bool   Play        (SDL_Renderer * render);
	bool   miniMax     (SDL_Renderer * render, int LEVEL);
	bool   gameWithMCTS(SDL_Renderer * render);
	
	void   initBoard();
	void   drawCurrentBoard(SDL_Renderer * render);
	int *  getPiece(int);
	void   selectSquare(int * from, int type,SDL_Renderer * render);
	int *  pixelToIndex(int x, int y);
	void   indexToPixel(SDL_Rect * R, int * From);
	void   print();
	void   setPiecesType(int TYPE);

	void   selectPossibilityOfMovment(int * from, SDL_Renderer * render);
	void   selectDisc(int x, int y, SDL_Renderer * render);

	void   check(SDL_Renderer * render);
	void   win(SDL_Renderer * render, int type);


	SDL_Surface  * board    =  IMG_Load("./image/board.png");
	SDL_Surface  * select1  =  IMG_Load("./image/pieceSelected.png");
	SDL_Surface  * select2  =  IMG_Load("./image/pieceSelected_.png");
	SDL_Surface  * disc     =  IMG_Load("./image/Disc.png");
	SDL_Surface  * select3  =  IMG_Load("./image/beAttention.png");
	SDL_Surface  * WWin     =  IMG_Load("./image/Wwin.png");
	SDL_Surface  * BWin     =  IMG_Load("./image/Bwin.png");
	SDL_Texture  * texture;
	SDL_Texture  * texturePiece;
	SDL_Rect rectPiece={20,22,78,78};

	int pieceType = 1;// 1 for whites pieces and -1 for blacks pieces
	int turn;

	int virtualBoard[8][8];
	int currentBoard[8][8];
	int BOARD[8][8];

	Move   *  M           = new Move(pieceType);
	Engine *  ENGINE      = new Engine();
	MCTS   *  ENGINE_MCTS = new MCTS();

	SDL_Surface *piece[6][2]={
		{IMG_Load("./image/wP.png"),IMG_Load("./image/bP.png")},
		{IMG_Load("./image/wR.png"),IMG_Load("./image/bR.png")},
		{IMG_Load("./image/wN.png"),IMG_Load("./image/bN.png")},
		{IMG_Load("./image/wB.png"),IMG_Load("./image/bB.png")},
		{IMG_Load("./image/wQ.png"),IMG_Load("./image/bQ.png")},
		{IMG_Load("./image/wK.png"),IMG_Load("./image/bK.png")}
	};
};