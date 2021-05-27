#pragma once

class Image;
class TerrainInfo
{
private:
	Image* img;
	int typeIndex;

public:
	void Init(int typeIndex, string imgName);
	Image* GetImg();
};

