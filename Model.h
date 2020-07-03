#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <d3dx11.h>
#include <windows.h>
#include <dxerr.h>
#include <xnamath.h>
#include "objfilemodel.h"

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT

//NPC values
struct NPC
{
	bool  movingLeft;
	float RangeMin;
	float RangeMax;
	float currValue;
};

//Correct alignment
template <size_t align> class AlignedAllocPolicy
{
public:
	void* operator new(std::size_t size)
	{
		return _aligned_malloc(size, align);
	}

	void operator delete(void* mem)
	{
		_aligned_free(mem);
	}
};
class Model: public AlignedAllocPolicy<16>
{
protected:
	ID3D11Device*				m_pD3DDevice;
	ID3D11DeviceContext*		m_pImmediateContext;

	ObjFileModel*				m_pObject;
	ID3D11VertexShader*			m_pVShader;
	ID3D11PixelShader*			m_pPShader;
	ID3D11InputLayout*			m_pInputLayout;
	ID3D11Buffer*				m_pConstantBuffer;
	ID3D11ShaderResourceView*	m_pTexture0;
	ID3D11SamplerState*			m_pSampler0;

	XMVECTOR					m_directional_light_shines_from;
	XMVECTOR					m_directional_light_colour;
	XMVECTOR					m_ambient_light_colour;
	XMVECTOR					m_model_centre_point;
	XMMATRIX					transposee;

	XMMATRIX world;

	float		 				m_x, m_y, m_z;
	float						m_xAngle, m_yAngle, m_zAngle;
	float						m_scaleX,m_scaleY,m_scaleZ,m_bounding_sphere_radius;

	float						m_dx, m_dz,m_yangle,m_gravity;
	float						min_x, min_y, min_z;
	float						max_x, max_y, max_z;
	NPC							npcData;
	const float SPEED = 0.01f;

public:

	Model(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext);
	Model(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, float posX, float posY, float posZ);
	Model(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, float posX, float posY, float posZ, float angleX, float angleY, float angleZ);
	Model(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, float posX, float posY, float posZ, float angleX, float angleY, float angleZ, float SCALE);
	Model(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, float posX, float posY, float posZ, float angleX, float angleY, float angleZ, float scaleX, float scaleY, float scaleZ);

	
	~Model();


	//Load a model from file
	virtual HRESULT LoadObjModel(char* filename);

	//Load a model from file and texture it
	virtual HRESULT LoadObjModel(char* filename, char* texturePath);

	//Gets
	XMFLOAT2 GetPosXZ();
	XMFLOAT3 GetPos();
	XMVECTOR getCentrePoint();
	XMVECTOR GetBoundingSphereWorldSpacePosition();
	float getScaleZ();
	float getMinZ();
	float getMinY();
	float getRadius();

	//Motion
	void MoveX(float x);
	void MoveY(float y);
	void MoveZ(float z);

	//Rotations
	void RotateX(float x);
	void RotateY(float y);
	void RotateZ(float z);

	//Gravity and Patrol data gather
	void ApplyGravity(float gravityForce);
	void AddPatrolData(float RangeMin, float RangeMax, float currValue, bool movingLeft);

	//Patrol NPC
	void NPCPatrol();
	
	//Calculate Model Center point
	void ModelCenterPoint();

	//Calculate Radius
	void CalculateRadius();

	//Returns the closest point to the given point inside a cube
	XMVECTOR IsPointInsideAABB(XMVECTOR point);

	//faces a given direction
	void LookAtXZ(float x, float z);

	//draw
	virtual void Draw(XMMATRIX* view, XMMATRIX* projection);

};

