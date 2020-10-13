#include "Map.h"
#include "Game.h"
#include <fstream>
#include <iostream>

Map::Map()
{

}

Map::Map(std::string tID, int ms, int ts)
{

}

Map::~Map() 
{
	
}


void Map::LoadMap(std::string pathToFile, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(pathToFile);

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {

			mapFile.get(tile);
			Game::AddTile(atoi(&tile), x * 32, y * 32);
			mapFile.ignore();

			std::cout << tile << ",";

		}

		std::cout << std::endl;
	}


	mapFile.close();
}