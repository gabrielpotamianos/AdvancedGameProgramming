#pragma once
#include "Model.h"
class Skybox01 :
	public Model
{
private:
	ID3D11Buffer*				m_pVertexBuffer;
	ID3D11RasterizerState*		m_pRasterSolid = 0;
	ID3D11RasterizerState*		m_pRasterSkyBox = 0;
	ID3D11DepthStencilState*	m_pDepthWriteSolid = 0;
	ID3D11DepthStencilState*	m_pDepthWriteSkyBox = 0;
public:
	Skybox01();
	Skybox01(ID3D11Device* g_pD3DDevice, ID3D11DeviceContext* g_pImmediateContext);
	Skybox01(ID3D11Device* g_pD3DDevice, ID3D11DeviceContext* g_pImmediateContext, float posX=0, float posY=0, float posZ=0,float xAngle=0,float yAngle=0, float zAngle=0, float Scale=1 );
	
	HRESULT LoadSkyBox();
	HRESULT LoadSkyBox(char* texturePath);

	void Draw(XMMATRIX* view, XMMATRIX* projection);
	
	~Skybox01();
};
