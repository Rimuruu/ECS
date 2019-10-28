#pragma once
#include "ECS.h"
#include "Inv.h"
#include "SpriteComponent.h"


class InputComponent : public Component {
private:

public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	InputComponent* input;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}
	void update() override {
		if (Inv::e.type == SDL_KEYDOWN) {
			switch (Inv::e.key.keysym.sym) {
			case SDLK_LEFT:
				transform->velocity.x = -1;
				sprite->Play("Right");
				break;
			case SDLK_RIGHT:
				transform->velocity.x = 1;
				sprite->Play("Left");
				break;
			}
		}
		else if (Inv::e.type == SDL_KEYUP) {
			switch (Inv::e.key.keysym.sym) {
			case SDLK_LEFT:
				if (transform->velocity.x < 0) { 
					sprite->Play("Idle");
					transform->velocity.x = 0; }
				break;
			case SDLK_RIGHT:
				if (transform->velocity.x > 0) {
					sprite->Play("Idle");
					transform->velocity.x = 0;
				}
				break;

			}


		}
	}

};