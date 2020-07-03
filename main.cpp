////The #include order is important
#include <d3d11.h>
#include "Game.h"


//////////////////////////////////////////////////////////////////////////////////////
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Game game(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	game.runGame();

	return S_OK;
}



