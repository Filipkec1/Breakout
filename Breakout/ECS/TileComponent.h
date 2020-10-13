#pragma once

#include "SDL.h"

class TileComponent : public Component
{
public:

	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* pathToFile;

	TileComponent() = default;

	TileComponent(int x, int y, int width, int height, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = width;
		tileRect.h = height;
		tileID = id;

		switch (tileID)
		{
		case 0:
			pathToFile = "./Assets/water.png";
			break;

		case 1:
			pathToFile = "./Assets/dirt.png";
			break;

		case 2:
			pathToFile = "./Assets/grass.png";
			break;
		}
	}

	void init() override
	{
		entity->addComponent<TransformComponent>(static_cast<float>(tileRect.x), static_cast<float>(tileRect.y), tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(pathToFile);
		sprite = &entity->getComponent<SpriteComponent>();
	}
};