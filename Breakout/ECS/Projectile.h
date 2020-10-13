#pragma once

#include "../Vector2D.h"

class ProjectileComponent : public Component
{
public:

	ProjectileComponent(int speed, Vector2D vel) : speed(speed), velocity(vel)
	{

	}

	~ProjectileComponent()
	{

	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void update() override
	{

	}

private:

	TransformComponent* transform;

	int speed;
	Vector2D velocity;

};