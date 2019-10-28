#pragma once
#include "ECS.h"
#include <string>
#include "TextureManager.h"
#include "TransformComponent.h"


class ColliderComponent : public Component {
public:
	SDL_Rect collider;
	std::string tag;
	SDL_Renderer* ren;
	TransformComponent* transform;
	int width,height,x,y;

	ColliderComponent() {
		tag = "null";
	}

	ColliderComponent(std::string tag, SDL_Renderer* ren,int width,int height,int x, int y) {
		this->tag = tag;
		this->ren = ren;
		this->width = width;
		this->height = height;
		this->x = x;
		this->y = y;
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		collider.x = transform->position.x+x;
		collider.y = transform->position.y+x;
		collider.w = width;
		collider.h = height;
	}

	void update() override {
		collider.x = transform->position.x+x;
		collider.y = transform->position.y+y;

	}

	void draw() override {
		SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
		SDL_RenderDrawRect(ren, &collider);
	}


};