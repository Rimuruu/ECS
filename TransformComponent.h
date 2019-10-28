#pragma once
#include "ECS.h"
#include "Vector2D.h"
class TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D velocity;
	int speed, width, height;
	int scale = 1;
	TransformComponent() {
		TransformComponent(0.0f, 0.0f);
	}

	TransformComponent(float x, float y,int w=128,int h=128,int speed = 3) {
		position.x = x;
		position.y = y;
		this->speed = speed;
		width = w;
		height = h;
	}

	void init() override{
		velocity.x = 0.0f;
		velocity.y = 0.0f;
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;


	}

};


