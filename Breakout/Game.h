#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
	public:
		Game();
		~Game();

		void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
		
		void handleEvents();
		void update();
		void render();
		void clean();

		bool running() { return isRunning;};

		static void AddTile(int id, int x, int y);
		static SDL_Renderer* renderer;
		static SDL_Event event;

		enum groupLabels : std::size_t
		{
			groupMap,
			groupPlayer,
			groupProjectile,
			groupColliders
		};

	private:
		bool isRunning;
		int count = 0;
		SDL_Window* window;
};

