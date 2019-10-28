#pragma once
#include "ECS.h"
#include "TextureManager.h"
#include "TransformComponent.h"
#include <iostream>
#include "Inv.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component {
public:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Renderer* ren;
	SDL_Rect srcRect, destRect;
	bool animated = false;
	int frames = 0;
	int speed = 100;
	int animeIndex = 0;
	std::map<const char*, Animation> animations;

	SpriteComponent() = default;
	SpriteComponent(const char* path, SDL_Renderer* ren) {

		texture = TextureManager::loadTexture(path);
		this->ren = ren;

	}
	SpriteComponent(const char* path, bool isAnimated) {

		texture = TextureManager::loadTexture(path);
		animated=isAnimated;

		Animation idle = Animation(0, 1, 100);
		Animation right = Animation(1, 2, 100);
		Animation left = Animation(2, 2, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Right", right);
		animations.emplace("Left", left);
		Play("Idle");

	

	}

	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 128;

		destRect.x =transform->position.x;
		destRect.y = transform->position.y;
		destRect.w = transform->width;
		destRect.h = transform->height;
	}


	void update() override {

		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		srcRect.y = animeIndex * transform->height;
		destRect.x = transform->position.x;
		destRect.y = transform->position.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;

	}

	void draw() override {

		SDL_RenderCopy(Inv::ren, texture, &srcRect, &destRect);
		
	}

	void Play(const char* animName) {
		frames = animations[animName].frames;
		animeIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

	

};