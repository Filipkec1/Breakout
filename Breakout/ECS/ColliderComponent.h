#pragma once

#include <string>
#include "SDL.h"
#include "ECS.h"
#include "TransformComponent.h"

class ColliderComponent : public Component
{
public:

	SDL_Rect collider;
	std::string tag;

	TransformComponent* transform;

	ColliderComponent(std::string tag)
	{
		this->tag = tag;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		//if(tag != "wall")
		//{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		//}
	}
};
