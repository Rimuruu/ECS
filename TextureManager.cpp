#include "TextureManager.h";
#include "Inv.h"


SDL_Texture* TextureManager::loadTexture(const char* filename) {
	SDL_Surface* Sprite = IMG_Load(filename);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Inv::ren, Sprite);
	return texture;
}