#pragma once
#include <SDL.h>

#include <SDL_image.h>
#include "Map.h"
class Inv{
private:
  	SDL_Window *win;
   
   bool isRunning;
   bool pause;
   int FPS;
   Uint32 frameDelay;
   int frameMax; //???
   int frame;
   int frameCount;
   int frameStart;
   Map* map;

public:
	static SDL_Renderer* ren;
	static SDL_Event e;
	static SDL_Texture* allTexture;
	static void addTile(int srcX,int srcY,int xpos,int ypos);
	Inv();
	~Inv();
	int run(); 
	int update(); // ???
	int cleanup();
	int event();
	int render();
};