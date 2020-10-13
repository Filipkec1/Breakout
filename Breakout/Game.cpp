#pragma once

#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
Manager manager;

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;

auto& player(manager.addEntity());
auto& projectile(manager.addEntity());
auto& wallL(manager.addEntity());
auto& wallR(manager.addEntity());
auto& wallT(manager.addEntity());
auto& wallB(manager.addEntity());

Game::Game()
{
	
}

Game::~Game()
{}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::printf("Subsystem Initialized\n");

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window) {
			std::printf("Window created\n");
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::printf("Renderer created\n");
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	int sizeX = 16;
	int sizeY = 16;

	//map = new Map();
	//Map::LoadMap("./Assets/16x16.map", sizeX, sizeY);

	player.addComponent<TransformComponent>(140.0f, 480.0f, 16, 32, 1);
	player.addComponent<SpriteComponent>("./Assets/grass.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayer);

	wallL.addComponent<TransformComponent>(400.0f, 100.0f, 400, 20, 1);
	wallL.addComponent<SpriteComponent>("./Assets/wall.png");
	wallL.addComponent<ColliderComponent>("wall");
	wallL.addGroup(groupColliders);

	wallR.addComponent<TransformComponent>(100.0f, 100.0f, 400, 20, 1);
	wallR.addComponent<SpriteComponent>("./Assets/water.png");
	wallR.addComponent<ColliderComponent>("wall");
	wallR.addGroup(groupColliders);

	wallT.addComponent<TransformComponent>(100.0f, 100.0f, 20, 300, 1);
	wallT.addComponent<SpriteComponent>("./Assets/grass.png");
	wallT.addComponent<ColliderComponent>("wall");
	wallT.addGroup(groupColliders);

	wallB.addComponent<TransformComponent>(100.0f, 500.0f, 20, 320, 1);
	wallB.addComponent<ColliderComponent>("wall");
	wallB.addGroup(groupColliders);

	projectile.addComponent<TransformComponent>(200.0f, 400.0f, 16, 16, 1);
	projectile.addComponent<SpriteComponent>("./Assets/dirt.png");
	projectile.addComponent<ProjectileComponent>(50, Vector2D(1.0f, -1.0f));
	projectile.addComponent<ColliderComponent>("test");
	projectile.addGroup(Game::groupProjectile);
}

auto& test(manager.getGroup(Game::groupProjectile));
auto& players(manager.getGroup(Game::groupPlayer));
auto& colliders(manager.getGroup(Game::groupColliders));

void Game::handleEvents() 
{
	SDL_PollEvent(&event);

	switch (event.type){
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update() 
{
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	Vector2D projetPos = projectile.getComponent<TransformComponent>().position;
	Vector2D projetVel = projectile.getComponent<TransformComponent>().velocity;

	manager.refresh();
	manager.update();

	for (auto c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;

		if (Collision::AABB(cCol, player.getComponent<ColliderComponent>().collider))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}

		switch (Collision::AABBLR(cCol, projectile.getComponent<ColliderComponent>().collider))
		{
		case 0:
			break;

		case 1:
			projetVel.y = projetVel.y * -1;
			projectile.getComponent<TransformComponent>().velocity = projetVel;
			break;

		case 2:
			projetVel.x = projetVel.x * -1;
			projectile.getComponent<TransformComponent>().velocity = projetVel;
			break;
		}
	}

	switch (Collision::AABBLR(player.getComponent<ColliderComponent>().collider, projectile.getComponent<ColliderComponent>().collider))
	{
	case 0:
		break;

	case 1:
		projetVel.y = projetVel.y * -1;
		projectile.getComponent<TransformComponent>().velocity = projetVel;
		break;

	case 2:
		projetVel.x = projetVel.x * -1;
		projectile.getComponent<TransformComponent>().velocity = projetVel;
		break;
	}

}

void Game::render() 
{
	SDL_RenderClear(renderer);
	for (auto& t : test)
	{
		t->draw();
	}

	for (auto& c : colliders)
	{
		c->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::printf("Game cleaned\n");
}

void Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x,y,32,32, id);
	tile.addGroup(groupMap);
}