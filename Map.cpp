#include "Inv.h"
#include "Map.h"
Map::Map(){}
Map::~Map(){}


void Map::loadMap(std::string path, int sizeX, int sizeY) {
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = -sizeY+4; y <= 4; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			srcY = atoi(&c) * 128;
			mapFile.get(c);
			srcX = atoi(&c) * 128;
			Inv::addTile(srcX, srcY, x * 128, y*128);

			mapFile.ignore();
		}
		
	}

	mapFile.close();

}