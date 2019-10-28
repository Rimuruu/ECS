#pragma once
#include <string>
#include <fstream>
class Map {
public:
	Map();
	~Map();
	static void loadMap(std::string path, int sizeX, int sizeY);



};