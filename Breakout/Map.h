#pragma once

#include <string>

class Map
{
public:

	Map();
	Map(std::string tID, int ms, int ts);
	~Map();

	static void LoadMap(std::string pathToFile, int sizeX, int sizeY);

private:

	std::string texID;
};

