#include "Inv.h"
#include <iostream>
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Vector2D.h"
#include "ColliderComponent.h"
#include "TileComponent.h"

using namespace std;

Manager manager;
auto& player(manager.addEntity());
SDL_Renderer* Inv::ren;
SDL_Event Inv::e;
SDL_Texture* Inv::allTexture;
const char* lvl = "lvl1.map";
enum groupLaberls : std::size_t
{
	groupMap,
	groupPlayer,
	groupEnemies,
	groupColliders
};

auto& players(manager.getGroup(groupPlayer));
auto& tiles(manager.getGroup(groupMap));


Inv::Inv(){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout << "SDL not init" << endl;
    }
	
	if ((!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) cout << "SDLimage not init" << endl;
   win = SDL_CreateWindow("Framerate test SDL", 100, 100, 768, 640, SDL_WINDOW_SHOWN);
   ren = SDL_CreateRenderer(win, -1,    SDL_RENDERER_ACCELERATED);
   isRunning = true;
   FPS = 60;
   frame = 1000/60;
   frameCount = 0;
   map = new Map();
   allTexture = TextureManager::loadTexture("asset/spritesheet.png");
   Map::loadMap(lvl,6,29);
   player.addComponent<TransformComponent>(800/2-64,600-128,128,128,5);
   player.addComponent<SpriteComponent>("asset/shipsprite.png",true);
   player.addComponent<ColliderComponent>("hitbox",ren,128,64,0,64);
   player.addComponent<ColliderComponent>("hitbox2", ren, 64, 64, 32, 0);
   player.addComponent<InputComponent>();
   player.addGroup(groupPlayer);
   pause = true;



}

Inv::~Inv() {
	

}

int Inv::run(){
		frameStart = SDL_GetTicks();
	while(isRunning){
		frameDelay=SDL_GetTicks();
		event();
		
		if (!pause)
		{
			update();
			render();
			
		}
		
		frameCount++;
		frameMax = SDL_GetTicks()-frameDelay; 
		
		if (frameMax<frame)
		{
			SDL_Delay(frame-frameMax);
		}
	
		if (SDL_GetTicks()-frameStart>=1000)
		{
			frameStart=SDL_GetTicks();
			cout << "FPS : " << frameCount << " ticks :" << frame-frameMax << endl;
			frameCount=0;
		}
	}
	cleanup();
	SDL_Quit();
	cout << "SDL quit"<< endl;
	return 0;
}



int Inv::render(){
	SDL_SetRenderDrawColor(ren, 0,0,0 , 255);
	
	
	SDL_RenderClear(ren);
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}

	SDL_RenderPresent(ren);
	return 0;
	

}

int Inv::update() {
	manager.refresh();
	manager.update();
	return 0; 
}

int Inv::cleanup(){
	IMG_Quit();
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	cout << "Cleanup done"<< endl;
	SDL_Quit();
	return 0;
}

int Inv::event(){
	SDL_PollEvent(&e);
	switch (e.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_SPACE)
		{
			pause = !pause;
		}
	default:
		break;
	}
	


	return 0;
}

void Inv::addTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TransformComponent>(xpos, ypos);
	tile.addComponent<TileComponent>(srcX,srcY, xpos,ypos);

	tile.addGroup(groupMap);
}