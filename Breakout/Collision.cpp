#include "Collision.h"
#include "ECS/ColliderComponent.h"


bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	if (
		rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y
		)
	{
		return true;
	}

	return false;
}

int Collision::AABBLR(const SDL_Rect& rectA, const SDL_Rect& rectB)
{

	if (AABB(rectA, rectB)) {

		if (
			((rectA.x + rectA.w)-2 > rectB.x &&
			(rectB.x + rectB.w)-2 > rectA.x) &&
			(rectA.y + rectA.h > rectB.y &&
			rectB.y + rectB.h > rectA.y))
		{
			std::cout << rectA.x + rectA.w << "," << rectA.y + rectA.y << " A x1"<< std::endl;
			std::cout << rectB.x + rectB.w << "," << rectB.y + rectB.y << " B x1"<< std::endl;

			return 1;
		}

		if (
			(rectA.x + rectA.w > rectB.x &&
			rectB.x + rectB.w > rectA.x) &&
			(rectA.y + rectA.h > rectB.y &&
			rectB.y + rectB.h > rectA.y))
		{

			std::cout << rectA.x + rectA.w << "," << rectA.y + rectA.y << " A y1" << std::endl;
			std::cout << rectB.x + rectB.w << "," << rectB.y + rectB.y << " B y1" << std::endl;

			return 2;
		}
	}
	return 0;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider)) {	
		return true;
	}

	return false;
}

int  Collision::AABBLR(const ColliderComponent& colA, const ColliderComponent& colB)
{
	return AABBLR(colA.collider, colB.collider);
}