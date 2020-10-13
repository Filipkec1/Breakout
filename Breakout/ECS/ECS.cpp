#include "ECS.h"

void Entity::addGroup(Group mGroupe)
{
	groupBitSet[mGroupe] = true;

	manager.AddToGroupe(this, mGroupe);
}