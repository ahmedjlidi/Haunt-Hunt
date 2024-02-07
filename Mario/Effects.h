#pragma once
#include "Tile.h"

class Effects
{



public:
	Effects();

	void render(RenderTarget& target, Tile& tile, Shader* shader);
};

