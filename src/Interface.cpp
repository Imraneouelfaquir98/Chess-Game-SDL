	#include "../include/Interface.hpp"


	Interface::Interface(){
		SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow("Chess_GAME" 	,SDL_WINDOWPOS_UNDEFINED
												,SDL_WINDOWPOS_UNDEFINED
												,750,650
												,SDL_WINDOW_SHOWN);	

		render = SDL_CreateRenderer(window,-1,0);
		B = new Board(pieceType);
	}



	bool Interface::hoverButton(int x, int y, int w, int h, SDL_Surface * wind){
	    rectButton.x = x;
	    rectButton.y = y;
	    rectButton.w = w;
	    rectButton.h = h;
	    texture = SDL_CreateTextureFromSurface(render,hover_play);
	    SDL_RenderCopy(render,texture,NULL,&rectButton);
	    SDL_RenderPresent(render);
	    bool wait = true;
		while(wait){
			SDL_WaitEvent(&event);
			switch(event.type){

				case SDL_MOUSEBUTTONDOWN : //printf(" %d , %d \n",event.motion.x,event.motion.y);
					wait = false;
					waitSecondWindow = false;
					return true;
				break;

				case SDL_MOUSEMOTION :
					if(event.motion.x>x+w || event.motion.x<x || event.motion.y>y+h || event.motion.y<y){
						showWindow(wind);
						wait = false;
					}
				break;
			}
		}
		return false;
	}
	bool Interface::hoverBWTwoPlayer(int x, int y, int w, int h){
		rectButton.x = x;
	    rectButton.y = y;
	    rectButton.w = w;
	    rectButton.h = h;
	    texture = SDL_CreateTextureFromSurface(render,hover_play);
	    SDL_RenderCopy(render,texture,NULL,&rectButton);
	    SDL_RenderPresent(render);
	    bool wait = true;
		while(wait){
			SDL_WaitEvent(&event);
			switch(event.type){

				case SDL_MOUSEBUTTONDOWN : //printf(" %d , %d \n",event.motion.x,event.motion.y);
					wait = false;
					waitToPlayerWindow = false;
					return true;
				break;

				case SDL_MOUSEMOTION :
					if(event.motion.x>x+w || event.motion.x<x || event.motion.y>y+h || event.motion.y<y){
						showTwoPlayerWindow();
						wait = false;
					}
				break;
			}
		}
		return false;
	}



	void Interface::checkWhiteBlackButton(){
		if(pieceType == 1)
			rectBW.x = 274;
		else
			rectBW.x = 385;

		texture = SDL_CreateTextureFromSurface(render,hover_play);
	    SDL_RenderCopy(render,texture,NULL,&rectBW);
	}

	void Interface::showTwoPlayerWindow(){
		texture = SDL_CreateTextureFromSurface(render,windowWB);
		SDL_RenderCopy(render,texture,NULL,NULL);
		checkWhiteBlackButton();
		SDL_RenderPresent(render);
	}

	void Interface::windowOfTwoPlayers(){
		showTwoPlayerWindow();
		waitToPlayerWindow = true;

		while(waitToPlayerWindow){
			SDL_WaitEvent(&event);

			if(event.type == SDL_QUIT){
				continuer          = false;
				waitSecondWindow   = false;
				waitToPlayerWindow = false;
			}
			else if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION )
			{
				if(event.motion.x<52 && event.motion.y<40){
					if(hoverBWTwoPlayer(0,0,52,40)){
						waitToPlayerWindow = false;
						secondWindow();
					}
				}
				else if(event.motion.x<481 && event.motion.x>274 && event.motion.y<261 && event.motion.y>204){
					if(hoverBWTwoPlayer(275,202,202,52)){
						if(B->Play(render))
							windowOfTwoPlayers();
					}
				}
				
				else if(event.motion.x<482 && event.motion.x>385 && event.motion.y<321 && event.motion.y>276){
					if(hoverBWTwoPlayer(385,276,93,42)){
						pieceType = -1;
						B->setPiecesType(pieceType);
						windowOfTwoPlayers();
					}
				}

				else if(event.motion.x<370 && event.motion.x>274 && event.motion.y<321 && event.motion.y>276){
					if(hoverBWTwoPlayer(274,276,93,42)){
						pieceType = 1;
						B->setPiecesType(pieceType);
						windowOfTwoPlayers();
					}
				}
			}
		}
	}

	void Interface::firstWindow(){	
		showWindow(accueil);
		continuer = true;
		while(continuer){
			SDL_WaitEvent(&event);
			if(event.type == SDL_QUIT)
				continuer = false;
			else if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION){
				if(event.motion.x<480 && event.motion.x>276 && event.motion.y<297 && event.motion.y>244){
					if(hoverButton(275,242,202,52,accueil)){
						continuer  = false;
						secondWindow();
					}
				}
			}
		}
	}

	void Interface::secondWindow(){
		showWindow(choise);
		
		waitSecondWindow = true;

		while(waitSecondWindow){
			SDL_WaitEvent(&event);

			if(event.type == SDL_QUIT){
				continuer        = false;
				waitSecondWindow = false;
			}
			else if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
			{
				if(event.motion.x<363 && event.motion.x>164 && event.motion.y<312 && event.motion.y>255)
				{
					if(hoverButton(165,249,202,52,choise))
					{
						waitSecondWindow = false;
						// B->Play2(render);
						// B->gameWithMCTS(render);
						windowOfIA();
					}
				}
				else if(event.motion.x<599 && event.motion.x>402 && event.motion.y<312 && event.motion.y>255)
				{
					if(hoverButton(407,249,202,52,choise))
					{
						waitSecondWindow = false;
						windowOfTwoPlayers();
					}
				}
				else if(event.motion.x<52 && event.motion.y<40)
				{
					if(hoverButton(0,0,52,40,choise))
					{
						waitSecondWindow = false;
						firstWindow();
					}
				}
			}
		}
	}

	void Interface::showWindow(SDL_Surface * wind){
		texture = SDL_CreateTextureFromSurface(render,wind);
		SDL_RenderCopy(render,texture,NULL,NULL);
		SDL_RenderPresent(render);
	}

	void Interface::windowOfIA(){
		showWindow(windowIA);
		
		waitWindowOfIA = true;

		while(waitWindowOfIA){
			SDL_WaitEvent(&event);

			if(event.type == SDL_QUIT){
				continuer        = false;
				waitWindowOfIA   = false;
			}
			else if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
			{
				// printf(" %d %d\n",event.motion.x,event.motion.y);
				if(event.motion.x<363 && event.motion.x>164 && event.motion.y<350 && event.motion.y>248)
				{
					if(hoverButton(165,249,209,52,windowIA))
					{
						waitWindowOfIA = false;
						// B->gameWithMCTS(render);
						if(B->gameWithMCTS(render))
							windowOfIA();
					}
				}
				else if(event.motion.x<599 && event.motion.x>402 && event.motion.y<312 && event.motion.y>255)
				{
					if(hoverButton(407,249,202,52,windowIA))
					{
						waitWindowOfIA = false;
						windowMiniMax();
					}
				}
				else if(event.motion.x<52 && event.motion.y<40)
				{
					if(hoverButton(0,0,52,40,windowIA))
					{
						waitWindowOfIA = false;
						secondWindow();
					}
				}
			}
		}
	}

	void Interface::windowMiniMax(){
		showMiniMaxWindow();
		waitMiniMaxWindow = true;

		while(waitMiniMaxWindow){
			SDL_WaitEvent(&event);

			if(event.type == SDL_QUIT){
				continuer          = false;
				waitWindowOfIA     = false;
				waitMiniMaxWindow  = false;
				waitSecondWindow   = false;
				waitToPlayerWindow = false;
			}
			else if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION )
			{
				if(event.motion.x<52 && event.motion.y<40){
					if(hoverMinimax(0,0,52,40)){
						waitMiniMaxWindow = false;
						windowOfIA();
					}
				}
				else if(event.motion.x<458 && event.motion.x>295 && event.motion.y<261 && event.motion.y>204){
					if(hoverMinimax(294,202,162,55)){
						waitMiniMaxWindow = false;
						waitSecondWindow  = false;
						// firstWindow(); 	
						// B->miniMax(render,LEVEL_MINIMAX);
						if(B->miniMax(render,LEVEL_MINIMAX))
							windowMiniMax();
					}
				}
				else if(event.motion.x<496 && event.motion.x>255 && event.motion.y<345 && event.motion.y>303){
					int L = (event.motion.x - 256)/48 + 1;
					if(hoverMinimax(256 + 48*(L-1) ,303,48,38)){
						LEVEL_MINIMAX = (event.motion.x - 256)/48 + 1;
						windowMiniMax();
					}
				}
			}
		}
	}

	void Interface::checkLevelMiniMax(){
		rectMM.x = 256 + 48*(LEVEL_MINIMAX-1);

		texture = SDL_CreateTextureFromSurface(render,hover_play);
	    SDL_RenderCopy(render,texture,NULL,&rectMM);
	}

	void Interface::showMiniMaxWindow(){
		texture = SDL_CreateTextureFromSurface(render,windowMinimax);
		SDL_RenderCopy(render,texture,NULL,NULL);
		checkLevelMiniMax();
		SDL_RenderPresent(render);
	}

	bool Interface::hoverMinimax(int x, int y, int w, int h){
		rectButton.x = x;
	    rectButton.y = y;
	    rectButton.w = w;
	    rectButton.h = h;
	    texture = SDL_CreateTextureFromSurface(render,hover_play);
	    SDL_RenderCopy(render,texture,NULL,&rectButton);
	    SDL_RenderPresent(render);
	    bool wait = true;
		while(wait){
			SDL_WaitEvent(&event);
			switch(event.type){

				case SDL_MOUSEBUTTONDOWN : //printf(" %d , %d \n",event.motion.x,event.motion.y);
					wait = false;
					waitMiniMaxWindow = false;
					return true;
				break;

				case SDL_MOUSEMOTION :
					if(event.motion.x>x+w || event.motion.x<x || event.motion.y>y+h || event.motion.y<y){
						showMiniMaxWindow();
						wait = false;
					}
				break;
			}
		}
		return false;
	}