#include <iostream>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/Board.hpp"

class Interface
{
public:
	Interface();
	~Interface();

	bool hoverButton(int x, int y, int w, int h, SDL_Surface  * texture);
	bool hoverBWTwoPlayer(int x, int y, int w, int h);
	bool hoverMinimax    (int x, int y, int w, int h);//

	void firstWindow();
	void secondWindow();
	void windowOfIA();//
	void windowOfTwoPlayers();
	void windowMiniMax();//
	
	void checkLevelMiniMax();//
	void checkWhiteBlackButton();

	void showWindow(SDL_Surface * wind);
	void showTwoPlayerWindow();
	void showMiniMaxWindow();//

	SDL_Window   * window;
	SDL_Renderer * render;
	SDL_Event      event;
	SDL_Texture  * texture;
	SDL_Surface  * hover_play = IMG_Load("./image/hoverPlay.png");
	SDL_Surface  * accueil    = IMG_Load("./image/accueil.jpg");
	SDL_Surface  * choise     = IMG_Load("./image/ccccc.jpg");
	SDL_Surface  * windowWB   = IMG_Load("./image/1111.jpg");
	SDL_Surface  * windowIA      = IMG_Load("./image/windowOfIA.jpg");
	SDL_Surface  * windowMinimax = IMG_Load("./image/minimax.jpg");
		
	SDL_Rect       rectButton;
	SDL_Rect       rectBW =  {274,276,93,42};
	SDL_Rect       rectMM =  {400,303,48,38};

	bool continuer          = true;
	bool waitSecondWindow   = true;
	bool waitToPlayerWindow = true;
	bool waitWindowOfIA     = true;
	bool waitMiniMaxWindow  = true;

	int LEVEL_MINIMAX = 3;
	int  pieceType = 1;
	Board *B;
};
