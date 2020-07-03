#pragma once
#include <d3d11.h>
#include <xnamath.h>
#include <math.h>

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT

class Camera
{
private:
	float m_x, m_y, m_z, m_dx, m_dy, m_dz, m_camera_rotation, localRotation, globalRotation=0;
	XMVECTOR m_position, m_lookat, m_up;
	POINT globalCursor;
	HWND hWnd;
	
	//mouse sensitivity
	const float sensitivity = 25;

	//degrees rotated around a point ->ObitAroundPointXZ 
	float degrees = 0;

public:
	Camera(HWND hWnd, float x_pos, float y_pos, float z_pos, float camera_Rotation);
	
	//Rotate Camera by degrees
	void Rotate(float degrees);
	
	//Look at cursor position
	void LookAtCursorPos(HWND hWnd);

	//Regather the cursor position
	void windowResized();

	//update the look at vector
	void UpdateLookAt(XMFLOAT3 vector);

	//Gets
	float GetX();
	float GetY();
	float GetZ();

	//Orbit around a point on X - Z axis
	void OrbitAroundPointXZ(XMFLOAT2 pointXZ, float Radius);

	//Strafe related to the local position
	void StrafeX(float distanceX);

	//Strafe related to the local position
	void StrafeZ(float distanceZ);

	//Move camera on Y Z and X axis
	void MoveUpDown(float distance);
	void MoveForwardBackward(float distance);
	void MoveLeftRight(float distance);

	//Not working Reset view to initial position and rotation
	void ResetView();

	XMMATRIX GetViewMatrix();

};

