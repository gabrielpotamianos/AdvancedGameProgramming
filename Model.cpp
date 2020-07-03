#include "Model.h"

#define MODEL_DEFAULT_POSITION_X 0
#define	MODEL_DEFAULT_POSITION_Y 0
#define	MODEL_DEFAULT_POSITION_Z 5
#define	MODEL_DEFAULT_ROTATION 0
#define MODEL_DEFAULT_SCALE 1
#define	MODEL_DEFAULT_RADIUS 0
#define MODEL_DEFAULT_AMBIENT_COLOUR 0.5f
#define MODEL_DEFAULT_LIGHT_COLOUR 1
#define SPEED_REDUCER 3
struct MODEL_CONSTANT_BUFFER
{
	XMMATRIX WorldViewProjection;				//64 bytes

	XMVECTOR directional_light_vector;			//16 bytes
	XMVECTOR directional_light_colour;			//16 bytes
	XMVECTOR ambinet_light_colour;				//16 bytes

	//112 bytes
};

Model::Model(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext)
{
	m_pD3DDevice = pDevice;
	m_pImmediateContext = pImmediateContext;
	m_x = MODEL_DEFAULT_POSITION_X;
	m_y = MODEL_DEFAULT_POSITION_Y;
	m_z = MODEL_DEFAULT_POSITION_Z;
	m_xAngle = MODEL_DEFAULT_ROTATION;
	m_yAngle = MODEL_DEFAULT_ROTATION;
	m_zAngle = MODEL_DEFAULT_ROTATION;
	m_scaleX = m_scaleY = m_scaleZ = MODEL_DEFAULT_SCALE;
	m_bounding_sphere_radius = MODEL_DEFAULT_RADIUS;
	m_directional_light_shines_from	 = XMVectorSet(0.0f, 2,   -3.0f, 0.0f);
	m_directional_light_colour		 = XMVectorSet(MODEL_DEFAULT_LIGHT_COLOUR, MODEL_DEFAULT_LIGHT_COLOUR, MODEL_DEFAULT_LIGHT_COLOUR, 1.0f);//white
	m_ambient_light_colour			 = XMVectorSet(MODEL_DEFAULT_AMBIENT_COLOUR, MODEL_DEFAULT_AMBIENT_COLOUR, MODEL_DEFAULT_AMBIENT_COLOUR, 1.0f);//dark grey 



}

Model::Model(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, float posX, float posY, float posZ)
	: Model(pDevice, pImmediateContext)
{
	m_x = posX;
	m_y = posY;
	m_z = posZ;
}

Model::Model(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, float posX, float posY, float posZ, float angleX, float angleY, float angleZ)
	:Model(pDevice, pImmediateContext)
{
	m_x = posX;
	m_y = posY;
	m_z = posZ;
	m_xAngle = angleX;
	m_yAngle = angleY;
	m_zAngle = angleZ;

}

Model::Model(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, float posX, float posY, float posZ, float angleX, float angleY, float angleZ, float SCALE)
{
	m_x = posX;
	m_y = posY;
	m_z = posZ;
	m_xAngle = angleX;
	m_yAngle = angleY;
	m_zAngle = angleZ;
	m_scaleX = m_scaleY = m_scaleZ = SCALE;
}

Model::Model(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, float posX, float posY, float posZ, float angleX, float angleY, float angleZ, float scaleX, float scaleY, float scaleZ)
	: Model(pDevice, pImmediateContext)
{
	m_x = posX;
	m_y = posY;
	m_z = posZ;
	m_xAngle = angleX;
	m_yAngle = angleY;
	m_zAngle = angleZ;
	m_scaleX = scaleX;
	m_scaleY = scaleY;
	m_scaleZ = scaleZ;
}

Model::~Model()
{
	//cleaning
	if (m_pSampler0) m_pSampler0->Release();
	if (m_pTexture0) m_pTexture0->Release();
	if (m_pConstantBuffer) m_pConstantBuffer->Release();
	if (m_pInputLayout) m_pInputLayout->Release();
	if (m_pVShader) m_pVShader->Release();
	if (m_pPShader) m_pPShader->Release();
	if (m_pObject) m_pObject->~ObjFileModel();


}

HRESULT Model::LoadObjModel(char* filename)
{
	HRESULT hr;

	//Load Model
	m_pObject = new ObjFileModel(filename, m_pD3DDevice, m_pImmediateContext);

	//Check if loaded
	if (m_pObject->filename == "FILE NOT LOADED")
		return S_FALSE;

	//Create Constant Buffer
	D3D11_BUFFER_DESC constant_buffer_desc0;
	ZeroMemory(&constant_buffer_desc0, sizeof(constant_buffer_desc0));
	constant_buffer_desc0.Usage = D3D11_USAGE_DEFAULT;										//Allows use by CPU and GPU
	constant_buffer_desc0.ByteWidth = 112;							//Set the total size of the buffer (in this case, 3 vertices)
	constant_buffer_desc0.BindFlags = D3D11_BIND_CONSTANT_BUFFER;							//Set the type of buffer to vertex buffer


	hr = m_pD3DDevice->CreateBuffer(&constant_buffer_desc0, NULL, &m_pConstantBuffer);		//Create the buffer

	if (FAILED(hr))
		return hr;



	ID3DBlob* VS, * PS, * error;

	//Compile Vertex Shader
	hr = D3DX11CompileFromFile("model_shader.hlsl", 0, 0, "ModelVS", "vs_4_0", 0, 0, 0, &VS, &error, 0);

	if (error != 0)//Check for shader compilation error
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr))//Don't fail if error is just a warning
		{
			return hr;
		}
	}

	//Compile Pixel Shader
	hr = D3DX11CompileFromFile("model_shader.hlsl", 0, 0, "ModelPS", "ps_4_0", 0, 0, 0, &PS, &error, 0);

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

	//Create Input Layout
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

	//Calculate Model Center Point
	ModelCenterPoint();

	//Calculate Model Radius
	CalculateRadius();

	return S_OK;
}

HRESULT Model::LoadObjModel(char* filename, char* texturePath)
{
	//Load Object
	if (FAILED(LoadObjModel(filename)))
	{
		DXTRACE_MSG("Failed to Load Model");
		return S_FALSE;
	}

	//Create Sampler
	D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

	m_pD3DDevice->CreateSamplerState(&sampler_desc, &m_pSampler0);


	//Load Texture from file
	D3DX11CreateShaderResourceViewFromFile(m_pD3DDevice,
		texturePath, NULL, NULL, &m_pTexture0, NULL);


	return S_OK;
}

XMFLOAT2 Model::GetPosXZ()
{
	return { m_x,m_z };
}

XMFLOAT3 Model::GetPos()
{
	return { m_x,m_y,m_z };
}

float Model::getScaleZ()
{
	return m_scaleZ;
}

float Model::getMinZ()
{
	return min_z;
}

float Model::getMinY()
{
	return min_y;
}

float Model::getRadius()
{
	return m_bounding_sphere_radius;
}

XMVECTOR Model::getCentrePoint()
{
	return m_model_centre_point;
}

XMVECTOR Model::GetBoundingSphereWorldSpacePosition()
{
	XMMATRIX local;

	local = XMMatrixScaling(m_scaleX, m_scaleY, m_scaleZ);
	local *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_xAngle), m_yAngle, XMConvertToRadians(m_zAngle));
	local *= XMMatrixTranslation(m_x, m_y, m_z);

	XMVECTOR offset = m_model_centre_point;

	//model centre point transformed by world matrix resulting the world space model centre position
	offset = XMVector3Transform(offset, local);

	return offset;
}

void Model::MoveX(float x)
{
	//On moving update centre point position
	m_x += x;
	ModelCenterPoint();

}

void Model::MoveY(float y)
{
	//On moving update centre point position
	m_y += y;
	ModelCenterPoint();

}


void Model::MoveZ(float z)
{	
	//On moving update centre point position
	m_z += z;
	ModelCenterPoint();
}

void Model::RotateX(float x)
{
	m_xAngle += x;
}

void Model::RotateY(float y)
{
	m_yAngle += XMConvertToRadians(y);
}

void Model::RotateZ(float z)
{
	m_zAngle += z;
}

void Model::ApplyGravity(float gravityForce)
{
	m_y -= gravityForce;
}


void Model::AddPatrolData(float RangeMin, float RangeMax, float currValue,bool movingLeft)
{
	//Get the map size ( columns and rows ) 
	npcData.RangeMin = RangeMin;
	npcData.RangeMax = RangeMax;

	//get the position on the map
	npcData.currValue = currValue;

	//based on position assign if npc needs to move left or right
	npcData.movingLeft = movingLeft;
}

void Model::NPCPatrol()
{
	//if npc needs to move left and it is in range
	if (npcData.movingLeft && npcData.currValue > npcData.RangeMin)
	{
		// move on x axis towards the left * speed/ speed reducer
		MoveX(-(npcData.currValue) *SPEED/ SPEED_REDUCER);

		//move the value towards the left end
		npcData.currValue-=SPEED;


	}

	//if npc needs to momve right and it is in range
	else if (!npcData.movingLeft && npcData.currValue < npcData.RangeMax)
	{
		//move on x axis towards right * speed/ speed reducer
		MoveX((npcData.currValue)*SPEED/ SPEED_REDUCER);

		//move the value towards the right end
		npcData.currValue += SPEED;
	}

	//if the values has passed the range move change direction
	if (npcData.currValue >= npcData.RangeMax)
		npcData.movingLeft = true;
	if (npcData.currValue <= npcData.RangeMin)
		npcData.movingLeft = false;
}

void Model::ModelCenterPoint()
{
	//Get min and Max and find calculate the middle point 
	min_x = min_y = min_z = INT16_MAX;
	max_x = max_y = max_z = INT16_MIN;
	for (int i = 0; i < m_pObject->numverts; i++)
	{
		if (m_pObject->vertices[i].Pos.x < min_x)
			min_x = m_pObject->vertices[i].Pos.x;
		else if (m_pObject->vertices[i].Pos.x > max_x)
			max_x = m_pObject->vertices[i].Pos.x;

		if (m_pObject->vertices[i].Pos.y < min_y)
			min_y = m_pObject->vertices[i].Pos.y;
		else if (m_pObject->vertices[i].Pos.y > max_y)
			max_y = m_pObject->vertices[i].Pos.y;

		if (m_pObject->vertices[i].Pos.z < min_z)
			min_z = m_pObject->vertices[i].Pos.z;
		else if (m_pObject->vertices[i].Pos.z > max_z)
			max_z = m_pObject->vertices[i].Pos.z;
	}
	m_model_centre_point = XMVectorSet((min_x + max_x) / 2, (min_y + max_y) / 2, (min_z + max_z) / 2, 0.0f);
	

	//update min and max globally due to its use in Sphere AABB colision
	XMMATRIX local;

	local = XMMatrixScaling(m_scaleX, m_scaleY, m_scaleZ);
	local *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_xAngle), XMConvertToRadians(m_yAngle), XMConvertToRadians(m_zAngle));
	local *= XMMatrixTranslation(m_x, m_y, m_z);

	XMVECTOR min = { min_x,min_y,min_z,0.0f };
	XMVECTOR max = { max_x,max_y,max_z,0.0f };

	min = XMVector3Transform(min, local);
	max = XMVector3Transform(max, local);

	min_x = XMVectorGetX(min);
	min_y = XMVectorGetY(min);
	min_z = XMVectorGetZ(min);

	max_y = XMVectorGetY(max);
	max_x = XMVectorGetX(max);
	max_z = XMVectorGetZ(max);

}

void Model::CalculateRadius()
{
	float radius = 0;

	for (int i = 0; i < m_pObject->numverts; i++)
	{
		XMVECTOR vertex = { m_pObject->vertices[i].Pos.x,m_pObject->vertices[i].Pos.y,m_pObject->vertices[i].Pos.z,0.0f };
		XMStoreFloat(&radius, XMVector3Length(XMVectorSubtract(vertex, m_model_centre_point)));

		//get the bigger radius by calculating it with all vertecies
		if (radius> m_bounding_sphere_radius)
			m_bounding_sphere_radius = radius;
	}

	
}

XMVECTOR Model::IsPointInsideAABB(XMVECTOR point)
{
	//gather position
	float point_x = XMVectorGetX(point);
	float point_y = XMVectorGetY(point);
	float point_z = XMVectorGetZ(point);

	float new_x, new_y, new_z;

	//if it is not inside the box on X axis assign the max otherwise assign its value
	if (point_x < min_x)
		new_x = XMVectorGetX(m_model_centre_point) + min_x;
	else if(point_x>max_x)  
		new_x = XMVectorGetX(m_model_centre_point) + max_x;
	else if(point_x>=min_x && point_x<=max_x)
		new_x = XMVectorGetX(m_model_centre_point) + point_x;

	//if it is not inside the box on Y axis assign the max otherwise assign its value
	if (point_y < min_y)
		new_y = XMVectorGetY(m_model_centre_point) + min_y;
	else if(point_y>max_y)
		new_y = XMVectorGetY(m_model_centre_point) + max_y;
	else if (point_y >= min_y && point_y <= max_y)
		new_y = XMVectorGetY(m_model_centre_point) + point_y;

	//if it is not inside the box on Z axis assign the max otherwise assign its value
	if (point_z < min_z)
		new_z = XMVectorGetZ(m_model_centre_point) + min_z;
	else if (point_z > max_z)
		new_z = XMVectorGetZ(m_model_centre_point) + max_z;
	else if (point_z >= min_z && point_z <= max_z)
		new_z = XMVectorGetZ(m_model_centre_point) + point_z;


	
	return  { new_x,new_y ,new_z,0.0f };
}

void Model::LookAtXZ(float x, float z)
{
	//calculate angle relative to a point
	m_dx = x - m_x;
	m_dz = z - m_z;
	m_yangle = atan2(m_dx, m_dz);
	m_yAngle = XMConvertToDegrees( m_yangle);

}

void Model::Draw(XMMATRIX* view, XMMATRIX* projection)
{

	//transform by world matrix
	world = XMMatrixScaling(m_scaleX, m_scaleY, m_scaleZ);
	world *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_xAngle),XMConvertToRadians( m_yAngle), XMConvertToRadians(m_zAngle));
	world *= XMMatrixTranslation(m_x, m_y, m_z);

	
	MODEL_CONSTANT_BUFFER model_cb_values;
	model_cb_values.WorldViewProjection = world * (*view) * (*projection);

	XMMATRIX transpose = XMMatrixTranspose(world);

	//add the light
	model_cb_values.directional_light_colour = m_directional_light_colour;
	model_cb_values.ambinet_light_colour = m_ambient_light_colour;
	model_cb_values.directional_light_vector = XMVector3Transform(m_directional_light_shines_from, transpose);
	model_cb_values.directional_light_vector = XMVector3Normalize(model_cb_values.directional_light_vector);

	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, 0, &model_cb_values, 0, 0);

	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);


	m_pImmediateContext->PSSetSamplers(0, 1, &m_pSampler0);

	m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTexture0);

	m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);
	
	m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);
	
	m_pImmediateContext->IASetInputLayout(m_pInputLayout);


	m_pObject->Draw();

}
