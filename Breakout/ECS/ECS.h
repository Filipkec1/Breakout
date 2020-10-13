#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID() 
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentArray = std::array<Component*, maxComponents>;
using ComponentBitSet = std::bitset<maxComponents>;

using GroupBitSet = std::bitset<maxGroups>;

class Component
{
public:
	Entity* entity;

	virtual void init(){}
	virtual void update(){}
	virtual void draw(){}

	virtual ~Component(){}
};

class Entity 
{
public:

	Entity(Manager& mManager) : manager(mManager)
	{
		
	}

	void update()
	{
		for (auto& c : components) 
		{
			c->update();
		}
	}

	void draw() 
	{
		for (auto& c : components)
		{
			c->draw();
		}
	}

	bool isActive() const
	{
		return active;
	}

	void destroy() 
	{
		active = false;
	}

	bool hasGroup(Group mGroupe)
	{
		return groupBitSet[mGroupe];
	}

	void addGroup(Group mGroupe);

	void delGroup(Group mGroupe)
	{
		groupBitSet[mGroupe] = false;
	}

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&...mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();

		return *c;
	}

	template<typename T> T& getComponent()const 
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

private:

	Manager& manager;

	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

	GroupBitSet groupBitSet;
};

class Manager 
{
public:

	void update() 
	{
		for (auto& e : enities) {
			e->update();
		}
	}

	void draw() 
	{
		for (auto& e : enities) {
			e->draw();
		}
	}

	void refresh() 
	{

		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntitys[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
					{
						return !mEntity->isActive() || !mEntity->hasGroup(i);
					}),
				std::end(v));
		}

		enities.erase(std::remove_if(std::begin(enities), std::end(enities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(enities));
	}

	void AddToGroupe(Entity* mEnitiy, Group mGroup)
	{
		groupedEntitys[mGroup].emplace_back(mEnitiy);
	}

	std::vector<Entity*>& getGroup(Group mGroup) 
	{
		return groupedEntitys[mGroup];
	}

	Entity& addEntity() 
	{
		Entity* e = new Entity(*this);

		std::unique_ptr<Entity> uPtr{ e };
		enities.emplace_back(std::move(uPtr));

		return *e;
	}

private:
	std::vector<std::unique_ptr<Entity>> enities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntitys;
};