#pragma once
#ifndef RENDER_H

#define RENDER_H

#include <d3d11.h>
#include <dxgi.h>
#include <d3dx11.h>
#include <windows.h>
#include <dxerr.h>
#include <xnamath.h>

//Define vertex structure
struct CONSTANT_BUFFER0
{
	XMMATRIX WorldViewProjection;

	float Choice = -1;
	float RedAmount;
	XMFLOAT2 scale = { 1.0f,1.0f };
	XMFLOAT3 RGB = { 0,0,0 };
	float packing_bytes;

	XMFLOAT3 updatedPos = { 0,0,0 };
	float packing;
};
struct POS_COL_VERTEX//This will be added to and renamed in future tutorials
{
	XMFLOAT3	pos;
	XMFLOAT4	Col;
};


#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT

class Render
{
public:
	Render();
	XMMATRIX projection, world, view;

	float g_clear_colour[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	int colourIndex = 0;
	int vertexIndex = 0;




	CONSTANT_BUFFER0 cb0_values;

	char		g_TutorialName[100] = "Game Application\0";

	HINSTANCE				g_hInst = NULL;
	HWND					g_hWnd = NULL;
	D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;


	ID3D11Device* g_pD3DDevice = NULL;
	ID3D11DeviceContext* g_pImmediateContext = NULL;
	IDXGISwapChain* g_pSwapChain = NULL;
	ID3D11RenderTargetView* g_pBackBufferRTView = NULL;
	ID3D11Buffer* g_pVertexBuffer;
	ID3D11VertexShader* g_pVertexShader;
	ID3D11PixelShader* g_pPixelShader;
	ID3D11InputLayout* g_pInputLayout;
	ID3D11Buffer* g_pConstantBuffer0;
	ID3D11DepthStencilView* g_pZBuffer;

	HRESULT InitialiseWindow(HINSTANCE hInstance, int nCmdShow, WNDPROC wndProc);

	HRESULT InitialiseD3D();
	HRESULT InitialiseGraphics(POS_COL_VERTEX vertices[]);
	void RenderFrame(POS_COL_VERTEX vertices[]);
	void getRandomValues(XMFLOAT4& values);

	~Render();

};


#endif // !RENDER_H
