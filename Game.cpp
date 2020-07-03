#include "Game.h"
struct POS_COL_TEX_NORM_VERTEX//This will be added to and renamed in future tutorials
{
	XMFLOAT3	pos;
	XMFLOAT4	Col;
	XMFLOAT2	Texture0;
	XMFLOAT3	Normal;
};

//////////////////////////////////////////////////////////////////////////////////////
//	Global Variables
//////////////////////////////////////////////////////////////////////////////////////
HINSTANCE					g_hInst = NULL;
HWND						g_hWnd = NULL;
D3D_DRIVER_TYPE				g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL			g_featureLevel = D3D_FEATURE_LEVEL_11_0;
ID3D11Device*				g_pD3DDevice = NULL;
ID3D11DeviceContext*		g_pImmediateContext = NULL;
IDXGISwapChain*				g_pSwapChain = NULL;
ID3D11RenderTargetView*		g_pBackBufferRTView = NULL;
ID3D11SamplerState*			g_pSampler0;
ID3D11Buffer*				g_pVertexBuffer;
ID3D11VertexShader*			g_pVertexShader;
ID3D11PixelShader*			g_pPixelShader;
ID3D11InputLayout*			g_pInputLayout;
ID3D11Buffer*				g_pConstantBuffer0;
ID3D11DepthStencilView*		g_pZBuffer;
ID3D11ShaderResourceView*	g_pTexture0;
ID3D11BlendState*			g_pAlphaBlendEnable;
ID3D11BlendState*			g_pAlphaBlendDisable;
IDirectInput8*				g_direct_input;
IDirectInputDevice8*		g_keyboard_device;
MSG							msg = { 0 };


XMVECTOR					g_directional_light_shines_from;
XMVECTOR					g_directional_light_colour;
XMVECTOR					g_ambient_light_colour;
XMMATRIX					projection, world, view;
XMMATRIX					transpose;


Camera*						camera;
Text2D*						g_2DText;
Skybox01*					g_pSkyBox;
Model*						g_pFloorModel;
Model*						g_pModel1;
Model*						g_pPlayer;
time_t						g_time;

vector<Model*>				v_Models;

// 1 - Sphere NPC 
// This is a map considering for a easier placement of the models in the world 
vector<string>				g_map = {
	"000100000000000000",
	"000000100000000000",
	"000000000000000010",
	"000000000000001000",
	"000000000000000000",
	"000100000000000000",
	"000000000000001000",
	"100000000000000000",
	"000000100000000000",
	"000000000000010000",
	"000000000000000001",
	"100000000000000000"


};

//NPC Space to multiply with on initialisation
const int					MAP_SPACE_X_AXIS = 2.4f;
const int					MAP_SPACE_Y_AXIS = 9;
const int					SCREEN_WIDTH = 640;
const int					SCREEN_HEIGHT = 480;

int							score = 0;
float						lives = 3;
float						g_clear_colour[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
unsigned char				g_keyboard_keys_state[256];

#define TEXT_SIZE 0.08f
#define LIVES_POSITION 0.42f
#define SCREEN_MAX 1
#define SCREEN_MIN -1
#define GRAVITY 0.01f
#define PLAYER_SPEED 0.08f
#define CAMERA_INITIAL_POSITION_X 0
#define CAMERA_INITIAL_POSITION_Y 45
#define CAMERA_INITIAL_POSITION_Z -55
#define CAMERA_INITIAL_ROTATION 0
#define FLOOR_INITIAL_POSITION_X 3
#define FLOOR_INITIAL_POSITION_Y -4.5f
#define FLOOR_INITIAL_POSITION_Z 0
#define FLOOR_INITIAL_ROTATION 0
#define FLOOR_INITIAL_SCALE .5f
#define PLAYER_INITIAL_POSITION_X 3
#define PLAYER_INITIAL_POSITION_Y 0
#define PLAYER_INITIAL_POSITION_Z 0
#define PLAYER_INITIAL_ROTATION_X 0
#define PLAYER_INITIAL_ROTATION_Y 0
#define PLAYER_INITIAL_ROTATION_Z 0
#define PLAYER_INITIAL_SCALE 1
#define NPC_SCALE 0.8f



char		g_WindowName[100] = "Gabriel Potamianos' Assessment\0";


void Game::ShutdownD3D()
{
	if (g_keyboard_device) g_keyboard_device->Unacquire(); g_keyboard_device->Release();
	if (g_direct_input) g_direct_input->Release();
	if (g_pFloorModel) delete g_pModel1; g_pModel1 = nullptr;
	if (g_pFloorModel) delete g_pFloorModel; g_pFloorModel = nullptr;
	if (g_pAlphaBlendDisable) g_pAlphaBlendDisable->Release();
	if (g_pAlphaBlendEnable) g_pAlphaBlendEnable->Release();
	if (g_pTexture0) g_pTexture0->Release();
	if (g_pSampler0) g_pSampler0->Release();
	if (camera) delete camera; camera = nullptr;
	if (g_pZBuffer) g_pZBuffer->Release();
	if (g_pConstantBuffer0) g_pConstantBuffer0->Release();
	if (g_pVertexBuffer) g_pVertexBuffer->Release();
	if (g_pInputLayout) g_pInputLayout->Release();
	if (g_pVertexShader) g_pVertexShader->Release();
	if (g_pPixelShader) g_pPixelShader->Release();
	if (g_pBackBufferRTView) g_pBackBufferRTView->Release();
	if (g_pSwapChain) g_pSwapChain->Release();
	if (g_pImmediateContext) g_pImmediateContext->Release();
	if (g_pD3DDevice) g_pD3DDevice->Release();

}
void Game::RenderFrame(void)
{
	//Read Inputs
	ReadInputStates();

	//Look at the player
	camera->UpdateLookAt(g_pPlayer->GetPos());

	// Clear the back buffer - choose a colour you like
	g_pImmediateContext->ClearRenderTargetView(g_pBackBufferRTView, g_clear_colour);

	//Clear ZBuffer
	g_pImmediateContext->ClearDepthStencilView(g_pZBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//Set Projection
	projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0f), SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 800.f);

	//Get Camera View Matrix
	view = camera->GetViewMatrix();

	//Select which primitive type to use //03-01
	g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Draw Floor
	g_pFloorModel->Draw(&view, &projection);

	g_pPlayer->Draw(&view, &projection);
	//g_pSkyBox->Draw(&view, &projection);


	
	for (int i = 0; i < v_Models.size(); i++)
	{
		//Every npc must patrol
		v_Models[i]->NPCPatrol();
		
		//Draw every npc
		v_Models[i]->Draw(&view, &projection);


		//Check if any npc has collided with the player
		if (checkCollisionShperes(g_pPlayer, v_Models[i]))
		{

			//if so, erase that specific npc
			v_Models.erase(v_Models.begin() + i);

			//reduce lives
			lives--;
		}

		//if any npc is behind the moving floor
		else if (g_pFloorModel->getMinZ() > v_Models[i]->GetPos().z)
		{
			//erase the model
			v_Models.erase(v_Models.begin());

			//increase score
			score++;
		}
	}

	//if lives are 0 or less, close the program
	if (lives <= 0)
		msg.message = WM_QUIT;

	if (v_Models.size() > 0)
	{
		//Moving Platform
		g_pFloorModel->MoveZ(0.01f);
	}
	else
	{
		//Display Won Text
		g_2DText->AddText("YOU WON!", SCREEN_MAX / 2, 0, TEXT_SIZE);
		
		//Create a smooth effect which stays a bit before closing the program
		lives -= 0.001f;

	}


	//Collision between player and platform
	if (!checkCollisionShpereAABB(g_pFloorModel, g_pPlayer))
	{
		//If no collision then apply gravity
		g_pPlayer->ApplyGravity(GRAVITY);

		//if the player under the platform
		if (g_pPlayer->GetPos().y < g_pFloorModel->getMinY())
		{
			//Display Lost Text
			g_2DText->AddText("YOU LOST!", SCREEN_MAX/2, 0, TEXT_SIZE);
			
			//Create a smooth effect which stays a bit before closing the program
			lives -= 0.001f;
		}

	}
	else
	{
		//If input is given Player moves, rotate the sphere to create a nice animation and move the camera with the player
		if (IsKeyPressd(DIK_D)) { g_pPlayer->MoveX(PLAYER_SPEED); g_pPlayer->RotateZ(-0.8f); camera->MoveLeftRight(PLAYER_SPEED); }
		if (IsKeyPressd(DIK_A)) { g_pPlayer->MoveX(-PLAYER_SPEED); g_pPlayer->RotateZ(0.8f); camera->MoveLeftRight(-PLAYER_SPEED); }
		if (IsKeyPressd(DIK_W)) { g_pPlayer->MoveZ(PLAYER_SPEED); g_pPlayer->RotateX(0.8f);  camera->MoveForwardBackward(PLAYER_SPEED); }
		if (IsKeyPressd(DIK_S)) { g_pPlayer->MoveZ(-PLAYER_SPEED); g_pPlayer->RotateX(-0.8f); camera->MoveForwardBackward(-PLAYER_SPEED); }

	}

	//Enable Alpha Channel Blend
	g_pImmediateContext->OMSetBlendState(g_pAlphaBlendEnable, 0, 0xffffffff);

	//create a string in which adds the the word "Score" and the actual score
	ostringstream SCORE;
	SCORE << "Score ";
	SCORE << score;

	//create text 
	g_2DText->AddText(SCORE.str(), SCREEN_MIN, SCREEN_MAX, TEXT_SIZE);

	//creates a string in which adds the word "Lives" and the actual lives
	ostringstream LIVES;
	LIVES << "Lives ";
	LIVES << lives;

	//create text
	g_2DText->AddText(LIVES.str(), LIVES_POSITION, SCREEN_MAX, TEXT_SIZE);


	//render text
	g_2DText->RenderText();


	//diables alpha channel blend
	g_pImmediateContext->OMSetBlendState(g_pAlphaBlendDisable, 0, 0xffffffff);

	// Display what has just been rendered
	g_pSwapChain->Present(0, 0);

}
Game::Game(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	view = XMMatrixIdentity();


	//Assign private function to a thread
	std::thread firstThread([this] {this->playsound(); });
	
	//Detach the thread so it can play simultaneously
	firstThread.detach();

	//Unreference parameteres
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//seed the time
	srand(time(NULL));


	//initialise window and check for errors
	if (FAILED(InitialiseWindow(hInstance, nCmdShow)))
	{
		DXTRACE_MSG("Failed to create Window");
		return;
	}

	//initialise input and check for errors
	if (FAILED(InitialiseInput()))
	{
		DXTRACE_MSG("FAILED TO INITIALISE INPUT");
		return;
	}

	//initialise graphics and check for errors
	if (FAILED(InitialiseD3D()))
	{
		MessageBox(g_hWnd, "Failed to initialise D3D", "INITIALISATION FAILED", MB_OK | MB_ICONERROR);
		return;
	}

	//initialise world and check for errors
	if (FAILED(InitialiseWorld()))
	{
		MessageBox(g_hWnd, "Graphics initialisation FAILED!", NULL, MB_OK);
		return;
	}

}

void Game::runGame()
{
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			RenderFrame();
	}

}

Game::~Game()
{
	ShutdownD3D();
}

HRESULT Game::InitialiseWindow(HINSTANCE hInstance, int nCmdShow)
{
	// Give your app your own name
	char Name[100] = "Hello World\0";

	// Register class
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	//   wcex.hbrBackground = (HBRUSH )( COLOR_WINDOW + 1); // Needed for non-D3D apps
	wcex.lpszClassName = Name;

	if (!RegisterClassEx(&wcex)) return E_FAIL;

	// Create window
	g_hInst = hInstance;
	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hWnd = CreateWindow(Name, g_WindowName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left,
		rc.bottom - rc.top, NULL, NULL, hInstance, NULL);
	if (!g_hWnd)
		return E_FAIL;

	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}

HRESULT Game::InitialiseD3D()
{
	HRESULT hr = S_OK;

	//get the client rectangle size
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;

#if defined(_DEBUG)
	// If the project is in a debug build, enable the debug layer.
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE, // comment out this line if you need to test D3D 11.0 functionality on hardware that doesn't support it
		D3D_DRIVER_TYPE_WARP, // comment this out also to use reference device
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	//Set and create Swap Chain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = g_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL,
			createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &g_pSwapChain,
			&g_pD3DDevice, &g_featureLevel, &g_pImmediateContext);
		if (SUCCEEDED(hr))
			break;
	}

	if (FAILED(hr))
		return hr;

	// Get pointer to back buffer texture
	ID3D11Texture2D* pBackBufferTexture;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		(LPVOID*)&pBackBufferTexture);

	if (FAILED(hr)) return hr;

	// Use the back buffer texture pointer to create the render target view
	hr = g_pD3DDevice->CreateRenderTargetView(pBackBufferTexture, NULL,
		&g_pBackBufferRTView);
	pBackBufferTexture->Release();

	if (FAILED(hr)) return hr;

	//Set and create Zbuffer texture
	D3D11_TEXTURE2D_DESC tex2dDesc;
	ZeroMemory(&tex2dDesc, sizeof(tex2dDesc));

	tex2dDesc.Width = width;
	tex2dDesc.Height = height;
	tex2dDesc.ArraySize = 1;
	tex2dDesc.MipLevels = 1;
	tex2dDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tex2dDesc.SampleDesc.Count = sd.SampleDesc.Count;
	tex2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex2dDesc.Usage = D3D11_USAGE_DEFAULT;

	ID3D11Texture2D* p_ZBufferTexture;
	hr = g_pD3DDevice->CreateTexture2D(&tex2dDesc, NULL, &p_ZBufferTexture);

	if (FAILED(hr)) return hr;

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));

	dsvDesc.Format = tex2dDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	//Create Zbuffer
	g_pD3DDevice->CreateDepthStencilView(p_ZBufferTexture, &dsvDesc, &g_pZBuffer);
	p_ZBufferTexture->Release();

	// Set the render target view
	g_pImmediateContext->OMSetRenderTargets(1, &g_pBackBufferRTView, g_pZBuffer);


	D3D11_BLEND_DESC b;
	b.RenderTarget[0].BlendEnable = TRUE;
	b.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	b.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	b.RenderTarget[0].DestBlend = D3D11_BLEND_DEST_ALPHA;
	b.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	b.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	b.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	b.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	b.IndependentBlendEnable = FALSE;
	b.AlphaToCoverageEnable = FALSE;

	g_pD3DDevice->CreateBlendState(&b, &g_pAlphaBlendEnable);

	//Import font
	g_2DText = new Text2D("assets/font1.bmp", g_pD3DDevice, g_pImmediateContext);


	// Set the viewport
	D3D11_VIEWPORT viewport;

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (FLOAT)width;
	viewport.Height = (FLOAT)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	g_pImmediateContext->RSSetViewports(1, &viewport);


	return S_OK;
}

HRESULT Game::InitialiseWorld(void)
{
	HRESULT hr = S_OK;

	//create camera
	camera = new Camera(g_hWnd, CAMERA_INITIAL_POSITION_X, CAMERA_INITIAL_POSITION_Y, CAMERA_INITIAL_POSITION_Z, CAMERA_INITIAL_ROTATION);

	//Rows and Columns of the map
	int ColumnCount = g_map[0].size();
	int RowCount = g_map.size();


	//create floor and import model
	g_pFloorModel = new Model(g_pD3DDevice, g_pImmediateContext, FLOOR_INITIAL_POSITION_X, FLOOR_INITIAL_POSITION_Y, FLOOR_INITIAL_POSITION_Z, FLOOR_INITIAL_ROTATION, FLOOR_INITIAL_ROTATION, FLOOR_INITIAL_ROTATION, ColumnCount, FLOOR_INITIAL_SCALE, RowCount);
	
	//Apply texture on loading and check for errors
	if (FAILED(g_pFloorModel->LoadObjModel((char*)"assets/cube.obj", (char*)"assets/skybox02.dds")))
	{
		MessageBox(g_hWnd, "Graphics initialisation FAILED!", NULL, MB_OK);
		return hr;
	}

	//create player and import model 
	g_pPlayer = new Model(g_pD3DDevice, g_pImmediateContext, PLAYER_INITIAL_POSITION_X, PLAYER_INITIAL_POSITION_Y, PLAYER_INITIAL_POSITION_Z, PLAYER_INITIAL_ROTATION_X, PLAYER_INITIAL_ROTATION_Y, PLAYER_INITIAL_ROTATION_Z, PLAYER_INITIAL_SCALE, PLAYER_INITIAL_SCALE, PLAYER_INITIAL_SCALE);
	
	//Apply texture on loading and check for errors
	if (FAILED(g_pPlayer->LoadObjModel((char*)"assets/Sphere.obj", (char*)"assets/rock.jpg")))
	{
		MessageBox(g_hWnd, "Graphics initialisation FAILED!", NULL, MB_OK);
		return hr;
	}

	
	for (int j = g_map.size() - 1; j >= 0; j--)
	{
		for (int i = 0; i < g_map[j].size(); i++)
		{

			//Every 1 represents a sphere on the map
			if (g_map[j][i] == '1')
			{

				//create it place it into the world according to the spaces 
				Model* g_pModel2 = new Model(g_pD3DDevice, g_pImmediateContext, (-ColumnCount / 2 + i * MAP_SPACE_X_AXIS), 0, (g_map.size() - j) * MAP_SPACE_Y_AXIS, 0, 0, 0, NPC_SCALE, NPC_SCALE, NPC_SCALE);
				if (FAILED(g_pModel2->LoadObjModel((char*)"assets/Sphere.obj", (char*)"assets/texture.bmp")))
				{
					MessageBox(g_hWnd, "Graphics initialisation FAILED!", NULL, MB_OK);
					return hr;
				}

				//add patrolling data
				g_pModel2->AddPatrolData(0, g_map[j].size(), i, i > (g_map[j].size() / 2));

				//push back the model
				v_Models.push_back(g_pModel2);

			}

		}
	}
	return S_OK;

}

HRESULT Game::InitialiseInput()
{
	HRESULT hr;
	ZeroMemory(&g_keyboard_keys_state, sizeof(g_keyboard_keys_state));

	hr = DirectInput8Create(g_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_direct_input, NULL);
	if (FAILED(hr)) return hr;

	hr = g_direct_input->CreateDevice(GUID_SysKeyboard, &g_keyboard_device, NULL);
	if (FAILED(hr)) return hr;


	hr = g_keyboard_device->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) return hr;

	hr = g_keyboard_device->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) return hr;

	hr = g_keyboard_device->Acquire();
	if (FAILED(hr)) return hr;

	return S_OK;
}

void Game::ReadInputStates()
{
	HRESULT hr;
	hr = g_keyboard_device->GetDeviceState(sizeof(g_keyboard_keys_state), (LPVOID)&g_keyboard_keys_state);
	if (FAILED(hr))
	{
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
			g_keyboard_device->Acquire();
	}

}

bool Game::IsKeyPressd(unsigned char DIkeycode)
{
	return g_keyboard_keys_state[DIkeycode] & 0x80;
}

bool Game::checkCollisionShperes(Model* m1, Model* m2)
{
	//get distance between world space center model position
	float distance;
	XMStoreFloat(&distance, XMVector3Length(XMVectorSubtract(m1->GetBoundingSphereWorldSpacePosition(), m2->GetBoundingSphereWorldSpacePosition())));

	//if the distance is less than radius = COLLISION
	if (m1->getRadius() + m2->getRadius() > distance)
		return true;

	return false;
}

bool Game::checkCollisionShpereAABB(Model* Cube, Model* Sphere)
{
	//Get the closest point inside AABB according to the sphere s world position
	XMVECTOR cubePointV = Cube->IsPointInsideAABB(Sphere->GetBoundingSphereWorldSpacePosition());

	//make the distance between the sphere position and the closest point 
	float distance;
	XMVECTOR distanceV = XMVectorSubtract(Sphere->GetBoundingSphereWorldSpacePosition(), cubePointV);
	XMStoreFloat(&distance, XMVector3Length(distanceV));

	//if the sphere radius is bigger than distance = COLLISION
	if (Sphere->getRadius() > distance)
		return true;

	return false;
}

void Game::playsound()
{
	PlaySound(TEXT("assets/wavSound.wav"), NULL, SND_SYNC);
}

LRESULT Game::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//necessary set up for the WndProc 
	Game* pThis;

	if (message == WM_NCCREATE)
	{
		pThis = static_cast<Game*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

		SetLastError(0);
		if (!SetWindowLongPtr(hWnd, GWL_USERDATA, reinterpret_cast<LONG_PTR>(pThis)))
		{
			if (GetLastError() != 0)
				return FALSE;
		}
	}
	else
	{
		pThis = reinterpret_cast<Game*>(GetWindowLongPtr(hWnd, GWL_USERDATA));
	}

	if (pThis)
	{
		PAINTSTRUCT ps;
		HDC hdc;

		switch (message)
		{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_SIZE:
			if (g_pSwapChain)
			{
				RECT rc;
				GetClientRect(g_hWnd, &rc);
				UINT width = rc.right - rc.left;
				UINT height = rc.bottom - rc.top;

				g_pImmediateContext->OMSetRenderTargets(0, 0, 0);

				// Release all outstanding references to the swap chain's buffers.
				g_pBackBufferRTView->Release();

				HRESULT hr;
				// Preserve the existing buffer count and format.
				// Automatically choose the width and height to match the client rect for HWNDs.
				hr = g_pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

				// Perform error handling here!

				// Get buffer and create a render-target-view.
				ID3D11Texture2D* pBuffer;
				hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
					(void**)&pBuffer);
				// Perform error handling here!
				hr = g_pD3DDevice->CreateRenderTargetView(pBuffer, NULL, &g_pBackBufferRTView);

				// Perform error handling here!
				pBuffer->Release();

				D3D11_TEXTURE2D_DESC tex2dDesc;
				ZeroMemory(&tex2dDesc, sizeof(tex2dDesc));

				tex2dDesc.Width = width;
				tex2dDesc.Height = height;
				tex2dDesc.ArraySize = 1;
				tex2dDesc.MipLevels = 1;
				tex2dDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				tex2dDesc.SampleDesc.Count = 1;
				tex2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
				tex2dDesc.Usage = D3D11_USAGE_DEFAULT;

				ID3D11Texture2D* p_ZBufferTexture;
				hr = g_pD3DDevice->CreateTexture2D(&tex2dDesc, NULL, &p_ZBufferTexture);

				if (FAILED(hr)) return hr;

				D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
				ZeroMemory(&dsvDesc, sizeof(dsvDesc));

				dsvDesc.Format = tex2dDesc.Format;
				dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;


				g_pD3DDevice->CreateDepthStencilView(p_ZBufferTexture, &dsvDesc, &g_pZBuffer);
				p_ZBufferTexture->Release();

				// Set the render target view
				g_pImmediateContext->OMSetRenderTargets(1, &g_pBackBufferRTView, g_pZBuffer);

				camera->windowResized();
				// Set up the viewport.
				D3D11_VIEWPORT vp;
				vp.Width = (FLOAT)width;
				vp.Height = (FLOAT)height;
				vp.MinDepth = 0.0f;
				vp.MaxDepth = 1.0f;
				vp.TopLeftX = 0;
				vp.TopLeftY = 0;
				g_pImmediateContext->RSSetViewports(1, &vp);

			}
			return 1;


		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);


}
