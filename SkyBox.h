#pragma once
#include "Model.h"
class SkyBox :
	public Model
{
private:
	ID3D11RasterizerState*			m_pRasterSolid = 0;
	ID3D11RasterizerState*			m_pRasterSkyBox = 0;
	ID3D11DepthStencilState*		m_pDepthWriteSolid = 0;
	ID3D11DepthStencilState*		m_pDepthWriteSkyBox = 0;
	ID3D11Buffer*					m_pVertexBuffer;
public:
	SkyBox(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext);
	SkyBox(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, float posX, float posY, float posZ);
	SkyBox(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, float posX, float posY, float posZ, float angleX, float angleY, float angleZ);
	SkyBox(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, float posX, float posY, float posZ, float angleX, float angleY, float angleZ, float SCALE);
	
	
	HRESULT LoadObjModel(char* filename);

	HRESULT LoadObjModel(char* filename, char* texturePath);


	void Draw(XMMATRIX* view, XMMATRIX* projection);

	~SkyBox();

};

