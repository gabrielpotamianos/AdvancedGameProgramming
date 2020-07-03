#include "Skybox01.h"
struct SKYBOX_CONSTANT_BUFFER
{
	XMMATRIX WorldViewProjection;				//64 bytes
};

struct POS_COL_TEX_VERTEX//This will be added to and renamed in future tutorials
{
	XMFLOAT3	pos;
	XMFLOAT4	Col;
	//XMFLOAT2	Texture0;
	//XMFLOAT3	Normal;
};

POS_COL_TEX_VERTEX vertices[] =
{
	//
	//	SECOND CUBE
	//
	//

//	//front
{XMFLOAT3(0.5f,  0.5f,	1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f)  },
{XMFLOAT3(0.5f, -0.5f,  1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)  },
{XMFLOAT3(-0.5f, -0.5f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)  },
																 
{XMFLOAT3(-0.5f, -0.5f,1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)  },
{XMFLOAT3(-0.5f,  0.5f,1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)  },
{XMFLOAT3(0.5f,  0.5f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)  },
																 
																 
//back															 
{XMFLOAT3(-0.5f,  0.5f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)  },
{XMFLOAT3(-0.5f, -0.5f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)  },
{XMFLOAT3(0.5f,  0.5f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)	  },
																 
{XMFLOAT3(0.5f,  0.5f, 2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)	  },
{XMFLOAT3(-0.5f, -0.5f, 2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
{XMFLOAT3(0.5f, -0.5f, 2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)	  },



//left
{XMFLOAT3(-0.5f, -0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)  },
{XMFLOAT3(-0.5f, -0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
{XMFLOAT3(-0.5f,  0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },

{XMFLOAT3(-0.5f, -0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
{XMFLOAT3(-0.5f,  0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
{XMFLOAT3(-0.5f,  0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },


//right
{XMFLOAT3(0.5f, -0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)  },
{XMFLOAT3(0.5f, -0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)   },
{XMFLOAT3(0.5f,  0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)   },

{XMFLOAT3(0.5f,  0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
{XMFLOAT3(0.5f, -0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
{XMFLOAT3(0.5f,  0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)   },


//bottom
{XMFLOAT3(0.5f, -0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)  },
{XMFLOAT3(0.5f, -0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
{XMFLOAT3(-0.5f, -0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },

{XMFLOAT3(0.5f, -0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
{XMFLOAT3(-0.5f, -0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
{XMFLOAT3(-0.5f, -0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },


//top
{XMFLOAT3(0.5f, 0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),   },
{XMFLOAT3(0.5f, 0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),     },
{XMFLOAT3(-0.5f, 0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),   },

{XMFLOAT3(-0.5f, 0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), },
{XMFLOAT3(0.5f, 0.5f,  2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),   },
{XMFLOAT3(-0.5f, 0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),   }
};


Skybox01::Skybox01(ID3D11Device* m_pD3DDevice, ID3D11DeviceContext* m_pImmediateContext)
	:Model(m_pD3DDevice, m_pImmediateContext)
{
}

Skybox01::Skybox01(ID3D11Device* m_pD3DDevice, ID3D11DeviceContext* m_pImmediateContext, float posX, float posY, float posZ, float xAngle, float yAngle, float zAngle, float Scale)
	: Model(m_pD3DDevice, m_pImmediateContext, posX, posY, posZ, xAngle, yAngle, zAngle, Scale)
{
}

HRESULT Skybox01::LoadSkyBox()
{
	HRESULT hr;

	//Set up and create vertex buffer
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
	constant_buffer_desc0.ByteWidth = 64;							//Set the total size of the buffer (in this case, 3 vertices)
	constant_buffer_desc0.BindFlags = D3D11_BIND_CONSTANT_BUFFER;							//Set the type of buffer to vertex buffer


	hr = m_pD3DDevice->CreateBuffer(&constant_buffer_desc0, NULL, &m_pConstantBuffer);		//Create the buffer

	if (FAILED(hr))
		return hr;

	ID3DBlob* VS, * PS, * error;
	hr = D3DX11CompileFromFile("skybox01_shader.hlsl", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, &error, 0);

	if (error != 0)//Check for shader compilation error
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr))//Don't fail if error is just a warning
		{
			return hr;
		}
	}

	hr = D3DX11CompileFromFile("skybox01_shader.hlsl", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, &error, 0);

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

	D3D11_INPUT_ELEMENT_DESC iedesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},

		{"COLOR", 0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
		
		//{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,0},

		//{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},

	};

	hr = m_pD3DDevice->CreateInputLayout(iedesc, ARRAYSIZE(iedesc), VS->GetBufferPointer(), VS->GetBufferSize(), &m_pInputLayout);
	if (FAILED(hr))
	{
		return hr;
	}

	m_pImmediateContext->IASetInputLayout(m_pInputLayout);

	m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);
	m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);

	return S_OK;
}

HRESULT Skybox01::LoadSkyBox(char* texturePath)
{
	HRESULT hr;

	//Loading cube
	hr = LoadSkyBox();
	if (FAILED(hr))
	{
		DXTRACE_MSG("Failed to LOAD SKYBOX");
		return S_FALSE;
	}



	///Creating sampler
	D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

	hr=m_pD3DDevice->CreateSamplerState(&sampler_desc, &m_pSampler0);
	if (FAILED(hr))
	{
		DXTRACE_MSG("Failed to CREATE SKYBOX SAMPLER");
		return S_FALSE;

	}


	//Creating Texture
	hr=D3DX11CreateShaderResourceViewFromFile(m_pD3DDevice,
		texturePath, NULL, NULL, &m_pTexture0, NULL);

	if (FAILED(hr))
	{
		DXTRACE_MSG("Failed to CREATE SKYBOX TEXTURE");
		return S_FALSE;

	}


	return S_OK;
}

void Skybox01::Draw(XMMATRIX* view, XMMATRIX* projection)
{

	world = XMMatrixScaling(m_scaleX, m_scaleY, m_scaleZ);
	world *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_xAngle), m_yAngle, XMConvertToRadians(m_zAngle));
	world *= XMMatrixTranslation(m_x, m_y, m_z);

	SKYBOX_CONSTANT_BUFFER skybox_cb_values;
	skybox_cb_values.WorldViewProjection = world * (*view) * (*projection);

	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, 0, &skybox_cb_values, 0, 0);

	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);

	m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//set vertex buffer //03-01
	UINT stride = sizeof(POS_COL_TEX_VERTEX);
	UINT offset = 0;
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//select which primitive type to use //03-01

	//m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTexture0);
	//m_pImmediateContext->PSSetSamplers(0, 1, &m_pSampler0);

	//draw the vertex buffer to the back buffer
	m_pImmediateContext->Draw(sizeof(vertices), 0);


}

Skybox01::~Skybox01()
{
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pRasterSolid) m_pRasterSolid->Release();
	if (m_pRasterSkyBox) m_pRasterSkyBox->Release();
	if (m_pDepthWriteSolid) m_pDepthWriteSolid->Release();
	if (m_pDepthWriteSkyBox) m_pDepthWriteSkyBox->Release();
}
