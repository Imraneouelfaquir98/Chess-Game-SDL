#include "../include/Board.hpp"
#include <cmath>

Board::Board(int TYPE)
{	
	pieceType = TYPE;
}

void Board::setPiecesType(int TYPE){
	pieceType = TYPE;
}

int * Board::getPiece(int indexPiece)
{
	int *pivot 	= (int*)malloc(sizeof(int)*2);
	pivot[0] 	= abs(indexPiece)-1;
	pivot[1]	= (indexPiece*pieceType > 0)?0:1;

	return pivot;
}

void Board::drawCurrentBoard(SDL_Renderer * render)
{
	texture = SDL_CreateTextureFromSurface(render,board);
	SDL_RenderCopy(render,texture,NULL,NULL);
	SDL_DestroyTexture(texture);

	int *pivot = (int*)malloc(sizeof(int)*2);

	for(int i=0 ; i<8 ; i++)
	{
		for(int j=0 ; j<8 ; j++)
		{
			if(currentBoard[i][j] != 0)
			{
				int T[2]={i,j};
				indexToPixel(&rectPiece,T);
				pivot = getPiece(currentBoard[i][j]);
				texturePiece = SDL_CreateTextureFromSurface(render,piece[pivot[0]][pivot[1]]);
				SDL_RenderCopy(render,texturePiece,NULL,&rectPiece);
				SDL_DestroyTexture(texturePiece);
			}
		} 	
	}
	// SDL_RenderPresent(render);
}

bool Board::Play(SDL_Renderer * render)
{
	M->setPieceType(pieceType);
	turn  = pieceType;
	bool continuer = 1;
	SDL_Event event;
	
	initBoard();
	drawCurrentBoard(render);
	SDL_RenderPresent(render);

	while(continuer)
	{	
		repeat1 :
		SDL_WaitEvent(&event);
		switch(event.type)
		{	
			case SDL_QUIT:
				continuer=0;
				break;
			case SDL_MOUSEBUTTONDOWN:  
				printf(" %d, %d \n",event.motion.x,event.motion.y);

				if(event.motion.x < 50 && event.motion.y < 50)
					return true;
				
				int *from, *to;
				bool wait = 1;

				from = pixelToIndex(event.motion.x,event.motion.y);
				if(turn*currentBoard[from[0]][from[1]]<0)
					goto repeat1;
				repeat2:
				selectSquare(from, 1,render);
				selectPossibilityOfMovment(from,render);
				SDL_RenderPresent(render);
				if( currentBoard[from[0]][from[1]] !=0 ){ printf(" From : %d  %d\n",from[0], from[1]);
					while(wait)
					{
						SDL_WaitEvent(&event);
						if(event.type == SDL_MOUSEBUTTONDOWN){
							to = pixelToIndex(event.motion.x,event.motion.y);

							if(currentBoard[to[0]][to[1]]*currentBoard[from[0]][from[1]] > 0){
								from[0] = to[0];
								from[1] = to[1];
								goto repeat2;
							} printf(" To : %d  %d\n",to[0],to[1]);

							if(abs(currentBoard[from[0]][from[1]]) !=6 && M->isMovmentPossible(from[0],from[1],to[0],to[1],currentBoard)  && !M->areTheKingCheckedFor(from[0],from[1],to[0],to[1],currentBoard,turn)){
								M->move(from,to,currentBoard); turn = -1*turn;  print();
								drawCurrentBoard(render);
								selectSquare(to  , 1,render);
								selectSquare(from, 2,render);
								SDL_RenderPresent(render); printf("\n\n");
								check(render);
							}	
							else if (abs(currentBoard[from[0]][from[1]]) == 6 && M->isMovmentPossible(from[0],from[1],to[0],to[1],currentBoard) && !M->isThisSquareChecked(to[0],to[1],currentBoard,turn)){
								M->move(from,to,currentBoard); turn = -1*turn; print();
								drawCurrentBoard(render);
								selectSquare(to  , 1,render);
								selectSquare(from, 2,render);
								SDL_RenderPresent(render);  printf("\n\n");
								check(render);
							}
							else{
								drawCurrentBoard(render);
								SDL_RenderPresent(render);
							}
							wait = 0;
						}
						else if(event.type == SDL_QUIT){
							wait = 0;
							continuer = 0;
						}
					}
				}

				break;
		}
	}

}

void Board::print()
{
	for(int i=0; i<8 ; i++)
	{
		for(int j=0 ; j<8 ; j++)
			printf("  %2d",currentBoard[i][j]);
		printf("\n");
	}
}

void Board::selectSquare(int * from, int type, SDL_Renderer * render)
{
	if(type == 1 && currentBoard[from[0]][from[1]]!=0)
	{
		drawCurrentBoard(render);
		int *pivot = (int*)malloc(sizeof(int)*2);

		indexToPixel(&rectPiece,from);
		texturePiece = SDL_CreateTextureFromSurface(render,select1);
		SDL_RenderCopy(render,texturePiece,NULL,&rectPiece);
		SDL_DestroyTexture(texturePiece);

		pivot = getPiece(currentBoard[from[0]][from[1]]);
		texturePiece = SDL_CreateTextureFromSurface(render,piece[pivot[0]][pivot[1]]);
		SDL_RenderCopy(render,texturePiece,NULL,&rectPiece);
		SDL_DestroyTexture(texturePiece);
	}
	else if (type ==2)
	{
		indexToPixel(&rectPiece,from);
		texturePiece = SDL_CreateTextureFromSurface(render,select2);
		SDL_RenderCopy(render,texturePiece,NULL,&rectPiece);
		SDL_DestroyTexture(texturePiece);
	}
}

void Board::check(SDL_Renderer * render){
	if(M->check(currentBoard,turn))
			win(render,pieceType*turn);
}

void Board::win(SDL_Renderer * render, int type){
	if(type == 1)
		texture = SDL_CreateTextureFromSurface(render,BWin);
	else
		texture = SDL_CreateTextureFromSurface(render,WWin);
	SDL_RenderCopy(render,texture,NULL,NULL);
	SDL_RenderPresent(render);
	SDL_Delay(5000);
	SDL_DestroyTexture(texture);
}



void Board::selectPossibilityOfMovment(int * from, SDL_Renderer * render){
	vector<vector<int>> POSSIBLEMOVMENTS;

	M->getPossibilityOfMovment(POSSIBLEMOVMENTS,from,currentBoard);

	for(int i=0; i<POSSIBLEMOVMENTS.size(); i++)
			selectDisc(POSSIBLEMOVMENTS[i][2],POSSIBLEMOVMENTS[i][3],render);
}

void Board::selectDisc(int x, int y, SDL_Renderer * render){
	int pivot[2] = {x,y};
	indexToPixel(&rectPiece,pivot);
	texturePiece = SDL_CreateTextureFromSurface(render,disc);
	SDL_RenderCopy(render,texturePiece,NULL,&rectPiece);
	SDL_DestroyTexture(texturePiece);
}



int * Board::pixelToIndex(int x, int y)  
{
	int * from = (int*)malloc(sizeof(int)*2);

	from[0] = (y - 21)/78;
	from[1] = (x - 71)/78;

	return from;
}

void  Board::indexToPixel(SDL_Rect * R, int * From)
{
	R->x = 70 + From[1]*76.5;
	R->y = 21 + From[0]*76.5;
}


void Board::initBoard(){
	for(int i=0 ; i<8 ; i++){
		currentBoard[1][i] = -1;
		currentBoard[6][i] =  1;
	}

	for(int i=2 ; i<6 ; i++){
		for(int j=0 ; j<8 ; j++)
			currentBoard[i][j] = 0;
	}

	for(int j=0 ; j<5 ; j++){
		currentBoard[0][j] = -j-2;
		currentBoard[7][j] =  j+2;
	}

	for(int j=5 ; j<8 ; j++){
		currentBoard[0][j] = -9+j;
		currentBoard[7][j] =  9-j;
	}

	if (pieceType == -1){
		currentBoard[0][3] = -6;  currentBoard[7][3] = 6;
		currentBoard[0][4] = -5;  currentBoard[7][4] = 5;
	}
}


bool Board::miniMax(SDL_Renderer * render, int LEVEL)
{
	M->setPieceType(pieceType);
	turn  = pieceType;
	bool continuer = 1;
	SDL_Event event;
	
	initBoard();
	// int BOARDD[8][8] = {
	// 		{  0,  0,  0,  0,  0,  0, -1, -6},
	// 		{  0,  0,  0,  0,  0,  0, -1, -1},
	// 		{  0,  0,  0,  0,  0,  0,  0,  0},
	// 		{  3,  0,  0,  0, -5,  0,  0,  0},
	// 		{  0,  0,  0,  2,  0,  0,  0,  0},
	// 		{  0,  0,  0,  0,  0,  1,  0,  0},
	// 		{  0,  0,  0,  0,  0,  0,  1,  1},
	// 		{  0,  0,  0,  0,  0,  0,  1,  6}
	// };
	// for(int i=0; i<8; i++)
	// 	for(int j=0; j<8; j++)
	// 		currentBoard[i][j] = BOARDD[i][j];
	drawCurrentBoard(render);
	SDL_RenderPresent(render);


	while(continuer)
	{	
		repeat1 :
		SDL_WaitEvent(&event);
		
		if(turn == 1){
			switch(event.type)
			{	
				case SDL_QUIT:
					continuer=0;
					break;
				case SDL_MOUSEBUTTONDOWN:  //printf(" %d, %d \n",event.motion.x,event.motion.y);

					if(event.motion.x < 50 && event.motion.y < 50)
						return true;
					
					int *from, *to;
					bool wait = 1;

					from = pixelToIndex(event.motion.x,event.motion.y);
					if(turn*currentBoard[from[0]][from[1]]<0)
						goto repeat1;
					repeat2:
					selectSquare(from, 1,render);
					selectPossibilityOfMovment(from,render);
					SDL_RenderPresent(render);
					if( currentBoard[from[0]][from[1]] !=0 ){ printf(" From : %d  %d\n",from[0], from[1]);
						while(wait)
						{
							SDL_WaitEvent(&event);
							if(event.type == SDL_MOUSEBUTTONDOWN){
								to = pixelToIndex(event.motion.x,event.motion.y);

								if(currentBoard[to[0]][to[1]]*currentBoard[from[0]][from[1]] > 0){
									from[0] = to[0];
									from[1] = to[1];
									goto repeat2;
								} printf(" To : %d  %d\n",to[0],to[1]);

								if(abs(currentBoard[from[0]][from[1]]) !=6 && M->isMovmentPossible(from[0],from[1],to[0],to[1],currentBoard)  && !M->areTheKingCheckedFor(from[0],from[1],to[0],to[1],currentBoard,turn)){
									M->move(from,to,currentBoard); turn = -1*turn;  print();
									drawCurrentBoard(render);
									selectSquare(to  , 1,render);
									selectSquare(from, 2,render);
									SDL_RenderPresent(render); printf("\n\n");
									check(render);
								}	
								else if (abs(currentBoard[from[0]][from[1]]) == 6 && M->isMovmentPossible(from[0],from[1],to[0],to[1],currentBoard) && !M->isThisSquareChecked(to[0],to[1],currentBoard,turn)){
									M->move(from,to,currentBoard); turn = -1*turn; print();
									drawCurrentBoard(render);
									selectSquare(to  , 1,render);
									selectSquare(from, 2,render);
									SDL_RenderPresent(render);  printf("\n\n");
									check(render);
								}
								else{
									drawCurrentBoard(render);
									SDL_RenderPresent(render);
								}
								wait = 0;
							}
							else if(event.type == SDL_QUIT){
								wait = 0;
								continuer = 0;
							}
						}
					}

					break;
			}
		}
		else{
			// vector<int> MV = ENGINE->generateMovment(currentBoard);
			vector<int> MV = ENGINE->minimaxRoot(currentBoard,-10000,10000,LEVEL);
			int from[2]={MV[0],MV[1]}, to[2] = {MV[2],MV[3]};
			printf("from %d %d, to %d %d\n",MV[0],MV[1],MV[2],MV[3]);
			M->move(from,to,currentBoard); turn = -1*turn;  print();
			drawCurrentBoard(render);
			selectSquare(to  , 1,render);
			selectSquare(from, 2,render);
			SDL_RenderPresent(render); printf("\n\n");
			check(render);
		}
	}

}


bool Board::gameWithMCTS(SDL_Renderer * render)
{
	M->setPieceType(pieceType);
	turn  = pieceType;
	bool continuer = 1;
	SDL_Event event;
	
	initBoard();
	ENGINE_MCTS->HEAD->copyBoard(currentBoard);
	ENGINE_MCTS->HEAD = ENGINE_MCTS->doIterations(1000);
	drawCurrentBoard(render);
	SDL_RenderPresent(render);


	while(continuer)
	{	
		repeat1 :
		SDL_WaitEvent(&event);
		
		if(turn == 1){
			switch(event.type)
			{	
				case SDL_QUIT:
					continuer=0;
					break;
				case SDL_MOUSEBUTTONDOWN:  //printf(" %d, %d \n",event.motion.x,event.motion.y);

					if(event.motion.x < 50 && event.motion.y < 50)
						return true;
					
					int *from, *to;
					bool wait = 1;

					from = pixelToIndex(event.motion.x,event.motion.y);
					if(turn*currentBoard[from[0]][from[1]]<0)
						goto repeat1;
					repeat2:
					selectSquare(from, 1,render);
					selectPossibilityOfMovment(from,render);
					SDL_RenderPresent(render);
					if( currentBoard[from[0]][from[1]] !=0 ){ printf(" From : %d  %d\n",from[0], from[1]);
						while(wait)
						{
							SDL_WaitEvent(&event);
							if(event.type == SDL_MOUSEBUTTONDOWN){
								to = pixelToIndex(event.motion.x,event.motion.y);

								if(currentBoard[to[0]][to[1]]*currentBoard[from[0]][from[1]] > 0){
									from[0] = to[0];
									from[1] = to[1];
									goto repeat2;
								} printf(" To : %d  %d\n",to[0],to[1]);

								if(abs(currentBoard[from[0]][from[1]]) !=6 && M->isMovmentPossible(from[0],from[1],to[0],to[1],currentBoard)  && !M->areTheKingCheckedFor(from[0],from[1],to[0],to[1],currentBoard,turn)){
									M->move(from,to,currentBoard); turn = -1*turn;  print();
									ENGINE_MCTS->HEAD = ENGINE_MCTS->setHead(from[0],from[1],to[0],to[1]);
									drawCurrentBoard(render);
									selectSquare(to  , 1,render);
									selectSquare(from, 2,render);
									SDL_RenderPresent(render); printf("\n\n");
									check(render);
								}	
								else if (abs(currentBoard[from[0]][from[1]]) == 6 && M->isMovmentPossible(from[0],from[1],to[0],to[1],currentBoard) && !M->isThisSquareChecked(to[0],to[1],currentBoard,turn)){
									M->move(from,to,currentBoard); turn = -1*turn; print();
									ENGINE_MCTS->HEAD = ENGINE_MCTS->setHead(from[0],from[1],to[0],to[1]);
									drawCurrentBoard(render);
									selectSquare(to  , 1,render);
									selectSquare(from, 2,render);
									SDL_RenderPresent(render);  printf("\n\n");
									check(render);
								}
								else{
									drawCurrentBoard(render);
									SDL_RenderPresent(render);
								}
								wait = 0;
							}
							else if(event.type == SDL_QUIT){
								wait = 0;
								continuer = 0;
							}
						}
					}

					break;
			}
		}
		else{
			ENGINE_MCTS->HEAD = ENGINE_MCTS->doIterations(1000);
			Node * BEST = ENGINE_MCTS->getTheBestAction();
			ENGINE_MCTS->HEAD = ENGINE_MCTS->setHead(BEST->ACTION[0],BEST->ACTION[1],BEST->ACTION[2],BEST->ACTION[3]);

			int from[2]={BEST->ACTION[0],BEST->ACTION[1]}, to[2] = {BEST->ACTION[2],BEST->ACTION[3]};
			printf("from %d %d, to %d %d\n",BEST->ACTION[0],BEST->ACTION[1],BEST->ACTION[2],BEST->ACTION[3]);
			M->move(from,to,currentBoard); turn = -1*turn;  print();
			drawCurrentBoard(render);
			selectSquare(to  , 1,render);
			selectSquare(from, 2,render);
			SDL_RenderPresent(render); printf("\n\n");
			check(render);
		}
	}

}