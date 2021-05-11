#pragma once

class Image;
enum class TerrainType { GRASS, DESERT, WINTER, GRAVEYARD, FIRE, END };
class TerrainInfo
{
private:
	Image* img;
	int typeIndex;

public:
	void Init(int typeIndex, string imgName);
	Image* GetImg();
};

