#pragma once

//////////////////////////////////////////////////////////////////////////////////////
//	Includes
//////////////////////////////////////////////////////////////////////////////////////
#include <d3d11.h>
#include <dxgi.h>
#include <d3dx11.h>
#include <windows.h>
#include <dxerr.h>
#include <xnamath.h>
#include <stdlib.h>
#include <time.h>
#include "Camera.h"
#include "text2D.h"
#include "Model.h"
#include <dinput.h>
#include "Skybox01.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <mmsystem.h>
#include <thread>
#include <ctime>


#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT



class Game
{

private:
	HRESULT InitialiseWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitialiseD3D();
	HRESULT InitialiseWorld(void);
	HRESULT InitialiseInput();
	void ReadInputStates();
	bool IsKeyPressd(unsigned char DIkeycode);

	bool checkCollisionShperes(Model* m1, Model* m2);
	bool checkCollisionShpereAABB(Model* Cube, Model* Sphere);
	void playsound();
	void ShutdownD3D();
	void RenderFrame(void);

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	Game(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow);
	void runGame();
	~Game();
};

