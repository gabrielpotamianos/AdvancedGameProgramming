#include "SkyBox.h"
struct POS_COL_TEX_NORM_VERTEX//This will be added to and renamed in future tutorials
{
	XMFLOAT3	pos;
	XMFLOAT4	Col;
	XMFLOAT2	Texture0;
	XMFLOAT3	Normal;
};

POS_COL_TEX_NORM_VERTEX vertices[] =
{

	//	//front
	{XMFLOAT3(0.5f,  0.5f,	1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(0.0f, 1.0f),XMFLOAT3(0.0f,0.0f,-1.0f)},
	{XMFLOAT3(0.5f, -0.5f,  1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(1.0f, 1.0f),XMFLOAT3(0.0f,0.0f,-1.0f)},
	{XMFLOAT3(-0.5f, -0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(1.0f, 0.0f),XMFLOAT3(0.0f,0.0f,-1.0f)},

	{XMFLOAT3(-0.5f, -0.5f,1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f),XMFLOAT3(0.0f,0.0f,-1.0f)},
	{XMFLOAT3(-0.5f,  0.5f,1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f),XMFLOAT3(0.0f,0.0f,-1.0f)},
	{XMFLOAT3(0.5f,  0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f),XMFLOAT3(0.0f,0.0f,-1.0f)},


	//back
	{XMFLOAT3(-0.5f,  0.5f, 2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(1.0f, 0.0f),XMFLOAT3(0.0f,0.0f,1.0f)},
	{XMFLOAT3(-0.5f, -0.5f, 2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(0.0f, 1.0f),XMFLOAT3(0.0f,0.0f,1.0f)},
	{XMFLOAT3(0.5f,  0.5f, 2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(1.0f, 1.0f) ,XMFLOAT3(0.0f,0.0f,1.0f)},

	{XMFLOAT3(0.5f,  0.5f, 2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(0.0f, 1.0f) ,XMFLOAT3(0.0f,0.0f,1.0f)},
	{XMFLOAT3(-0.5f, -0.5f, 2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(1.0f, 0.0f),XMFLOAT3(0.0f,0.0f,1.0f)},
	{XMFLOAT3(0.5f, -0.5f, 2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(1.0f, 1.0f) ,XMFLOAT3(0.0f,0.0f,1.0f)},



	//left
	{XMFLOAT3(-0.5f, -0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(0.0f, 1.0f) ,XMFLOAT3(-1.0f,0.0f,0.0f)},
	{XMFLOAT3(-0.5f, -0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(0.0f, 0.0f),XMFLOAT3(-1.0f,0.0f,0.0f)},
	{XMFLOAT3(-0.5f,  0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(1.0f, 1.0f) ,XMFLOAT3(-1.0f,0.0f,0.0f)},

	{XMFLOAT3(-0.5f, -0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(0.0f, 0.0f),XMFLOAT3(-1.0f,0.0f,0.0f)},
	{XMFLOAT3(-0.5f,  0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(1.0f, 0.0f),XMFLOAT3(-1.0f,0.0f,0.0f)},
	{XMFLOAT3(-0.5f,  0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(1.0f, 1.0f) ,XMFLOAT3(-1.0f,0.0f,0.0f)},


	//right
	{XMFLOAT3(0.5f, -0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(0.0f, 0.0f),XMFLOAT3(1.0f,0.0f,0.0f)},
	{XMFLOAT3(0.5f, -0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(0.0f, 1.0f) ,XMFLOAT3(1.0f,0.0f,0.0f)},
	{XMFLOAT3(0.5f,  0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(1.0f, 1.0f) ,XMFLOAT3(1.0f,0.0f,0.0f)},

	{XMFLOAT3(0.5f,  0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(1.0f, 0.0f),XMFLOAT3(1.0f,0.0f,0.0f)},
	{XMFLOAT3(0.5f, -0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(0.0f, 0.0f),XMFLOAT3(1.0f,0.0f,0.0f)},
	{XMFLOAT3(0.5f,  0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(1.0f, 1.0f) ,XMFLOAT3(1.0f,0.0f,0.0f)},


	//bottom
	{XMFLOAT3(0.5f, -0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) ,XMFLOAT2(1.0f, 1.0f),XMFLOAT3(0.0f,-1.0f,0.0f)},
	{XMFLOAT3(0.5f, -0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) ,XMFLOAT2(1.0f, 0.0f),XMFLOAT3(0.0f,-1.0f,0.0f)},
	{XMFLOAT3(-0.5f, -0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) ,XMFLOAT2(0.0f, 1.0f),XMFLOAT3(0.0f,-1.0f,0.0f)},

	{XMFLOAT3(0.5f, -0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(1.0f, 0.0f) ,XMFLOAT3(0.0f,-1.0f,0.0f)},
	{XMFLOAT3(-0.5f, -0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(0.0f, 0.0f),XMFLOAT3(0.0f,-1.0f,0.0f)},
	{XMFLOAT3(-0.5f, -0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(0.0f, 1.0f) ,XMFLOAT3(0.0f,-1.0f,0.0f)},


	//top
	{XMFLOAT3(0.5f, 0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(1.0f, 0.0f) ,XMFLOAT3(0.0f,1.0f,0.0f)},
	{XMFLOAT3(0.5f, 0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(1.0f, 1.0f)  ,XMFLOAT3(0.0f,1.0f,0.0f)},
	{XMFLOAT3(-0.5f, 0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(0.0f, 1.0f) ,XMFLOAT3(0.0f,1.0f,0.0f)},

	{XMFLOAT3(-0.5f, 0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(0.0f, 0.0f),XMFLOAT3(0.0f,1.0f,0.0f)},
	{XMFLOAT3(0.5f, 0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(1.0f, 0.0f) ,XMFLOAT3(0.0f,1.0f,0.0f)},
	{XMFLOAT3(-0.5f, 0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),XMFLOAT2(0.0f, 1.0f) ,XMFLOAT3(0.0f,1.0f,0.0f)}
};

struct MODEL_CONSTANT_BUFFER
{
	XMMATRIX WorldViewProjection;				//64 bytes


	//112 bytes
};

SkyBox::SkyBox(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext)
	:Model(pDevice, pImmediateContext)
{
	m_z = 0;
}

SkyBox::SkyBox(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, float posX, float posY, float posZ)
	: Model(pDevice, pImmediateContext, posX, posY, posZ)
{
}

SkyBox::SkyBox(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, float posX, float posY, float posZ, float angleX, float angleY, float angleZ)
	: Model(pDevice, pImmediateContext, posX, posY, posZ, angleX, angleY, angleZ)
{
}

SkyBox::SkyBox(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, float posX, float posY, float posZ, float angleX, float angleY, float angleZ, float SCALE)
	: Model(pDevice, pImmediateContext, posX, posY, posZ, angleX, angleY, angleZ, SCALE)
{
}



HRESULT SkyBox::LoadObjModel(char* filename)
{
	HRESULT hr;

	//m_pObject = new ObjFileModel(filename, m_pD3DDevice, m_pImmediateContext);

	//if (m_pObject->filename == "FILE NOT LOADED")
	//	return S_FALSE;

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;										//Allows use by CPU and GPU
	bufferDesc.ByteWidth = sizeof(vertices);							//Set the total size of the buffer (in this case, 3 vertices)
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;							//Set the type of buffer to vertex buffer
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;							//Allow access by the CPU
	hr = m_pD3DDevice->CreateBuffer(&bufferDesc, NULL, &m_pVertexBuffer);		//Create the buffer

	if (FAILED(hr))//Return an error code if failed
	{
		return hr;
	}

	//Copy the vertices into the buffer
	D3D11_MAPPED_SUBRESOURCE ms;

	//Lock the buffer to allow writing
	m_pImmediateContext->Map(m_pVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);

	//Copy the data
	memcpy(ms.pData, vertices, sizeof(vertices));

	//Unlock the buffer
	m_pImmediateContext->Unmap(m_pVertexBuffer, NULL);


	D3D11_BUFFER_DESC constant_buffer_desc0;
	ZeroMemory(&constant_buffer_desc0, sizeof(constant_buffer_desc0));
	constant_buffer_desc0.Usage = D3D11_USAGE_DEFAULT;										//Allows use by CPU and GPU
	constant_buffer_desc0.ByteWidth = sizeof(vertices);							//Set the total size of the buffer (in this case, 3 vertices)
	constant_buffer_desc0.BindFlags = D3D11_BIND_CONSTANT_BUFFER;							//Set the type of buffer to vertex buffer



	hr = m_pD3DDevice->CreateBuffer(&constant_buffer_desc0, NULL, &m_pConstantBuffer);		//Create the buffer

	if (FAILED(hr))
		return hr;

	ID3DBlob* VS, * PS, * error;
	hr = D3DX11CompileFromFile("skybox_shader.hlsl", 0, 0, "SkyBoxVS", "vs_4_0", 0, 0, 0, &VS, &error, 0);

	if (error != 0)//Check for shader compilation error
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr))//Don't fail if error is just a warning
		{
			return hr;
		}
	}

	hr = D3DX11CompileFromFile("skybox_shader.hlsl", 0, 0, "SkyBoxPS", "ps_4_0", 0, 0, 0, &PS, &error, 0);

	if (error != 0)//Check for shader compilation error
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr))//Don't fail if error is just a warning
		{
			return hr;
		}
	}

	//Create shader objects
	hr = m_pD3DDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_pVShader);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = m_pD3DDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pPShader);
	if (FAILED(hr))
	{
		return hr;
	}

	//Set the shader objects as active
	m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);
	m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);

	D3D11_INPUT_ELEMENT_DESC iedesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},

		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,0},

		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
	};

	hr = m_pD3DDevice->CreateInputLayout(iedesc, ARRAYSIZE(iedesc), VS->GetBufferPointer(), VS->GetBufferSize(), &m_pInputLayout);
	if (FAILED(hr))
	{
		return hr;
	}

	m_pImmediateContext->IASetInputLayout(m_pInputLayout);

	D3D11_RASTERIZER_DESC rasterizer_desc;
	ZeroMemory(&rasterizer_desc, sizeof(rasterizer_desc));

	rasterizer_desc.FillMode = D3D11_FILL_SOLID;
	rasterizer_desc.CullMode = D3D11_CULL_BACK;
	hr = m_pD3DDevice->CreateRasterizerState(&rasterizer_desc, &m_pRasterSolid);

	if (FAILED(hr))
		return hr;


	rasterizer_desc.FillMode = D3D11_FILL_SOLID;
	rasterizer_desc.CullMode = D3D11_CULL_FRONT;
	hr = m_pD3DDevice->CreateRasterizerState(&rasterizer_desc, &m_pRasterSkyBox);

	if (FAILED(hr))
		return hr;

	D3D11_DEPTH_STENCIL_DESC DSDecsc;
	ZeroMemory(&DSDecsc, sizeof(DSDecsc));
	DSDecsc.DepthEnable = true;
	DSDecsc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DSDecsc.DepthFunc = D3D11_COMPARISON_LESS;
	hr = m_pD3DDevice->CreateDepthStencilState(&DSDecsc, &m_pDepthWriteSolid);
	DSDecsc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	hr = m_pD3DDevice->CreateDepthStencilState(&DSDecsc, &m_pDepthWriteSkyBox);
	if (FAILED(hr))
		return hr;


	return S_OK;
}

HRESULT SkyBox::LoadObjModel(char* filename, char* texturePath)
{
	if (FAILED(LoadObjModel(filename)))
	{
		DXTRACE_MSG("Failed to Load Model");
		return S_FALSE;
	}

	D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

	m_pD3DDevice->CreateSamplerState(&sampler_desc, &m_pSampler0);
	HRESULT hr;
	D3DX11CreateShaderResourceViewFromFile(m_pD3DDevice,
		texturePath, NULL, NULL, &m_pTexture0, &hr);
	if (FAILED(hr))
	{
		DXTRACE_MSG("Failed to LOAD TEXTURE DDS");
		return S_FALSE;
	}
	return S_OK;
}

void SkyBox::Draw(XMMATRIX* view, XMMATRIX* projection)
{


	//m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	world = XMMatrixScaling(m_scale, m_scale, m_scale);
	//world *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_xAngle), m_yAngle, XMConvertToRadians(m_zAngle));
	world *= XMMatrixTranslation(m_x, m_y, m_z);

	MODEL_CONSTANT_BUFFER model_cb_values;
	model_cb_values.WorldViewProjection = world * (*view) * (*projection);

	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, 0, &model_cb_values, 0, 0);

	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	m_pImmediateContext->PSSetSamplers(0, 1, &m_pSampler0);

	m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTexture0);

	m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);

	m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);

	m_pImmediateContext->IASetInputLayout(m_pInputLayout);


	m_pImmediateContext->RSSetState(m_pRasterSkyBox);

	m_pImmediateContext->OMSetDepthStencilState(m_pDepthWriteSkyBox, NULL);

	UINT stride = sizeof(POS_COL_TEX_NORM_VERTEX);
	UINT offset = 0;
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	//m_pObject->Draw();
	m_pImmediateContext->Draw(sizeof(vertices), 0);

	m_pImmediateContext->OMSetDepthStencilState(m_pDepthWriteSolid, NULL);

	m_pImmediateContext->RSSetState(m_pRasterSolid);


}

SkyBox::~SkyBox()
{
	if (m_pDepthWriteSkyBox) m_pDepthWriteSkyBox->Release();
	if (m_pDepthWriteSolid) m_pDepthWriteSolid->Release();
	if (m_pRasterSkyBox) m_pRasterSkyBox->Release();
	if (m_pRasterSolid) m_pRasterSolid->Release();
}
