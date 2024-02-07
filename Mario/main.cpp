
#include "stdafx.h"
#include "Game.h"





int WinMain(int argc, wchar_t* argv[])
{

	srand(static_cast<unsigned>(time(nullptr)));
	Game* game = new Game();

	while (game->IsRunning())
	{
		game->run();
	}

	return 0;
}