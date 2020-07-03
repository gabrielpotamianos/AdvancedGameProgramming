#include "Camera.h"
#include <iostream>
Camera::Camera(HWND hWnd, float x_pos, float y_pos, float z_pos, float camera_Rotation)
	:m_x(x_pos), m_y(y_pos), m_z(z_pos), m_camera_rotation(XMConvertToRadians(camera_Rotation))
{
	//assigning data
	this->hWnd = hWnd;

	//calculating the angles
	m_dx = sin(m_camera_rotation);
	m_dz = cos(m_camera_rotation);

	//setting the values
	m_position = XMVectorSet(m_x, m_y, m_z, 0.0f);
	m_lookat = XMVectorSet(m_x + m_dx, m_y, m_z + m_dz, 0.0f);
	m_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//get cursor position on the screen
	RECT rect;
	GetClientRect(hWnd, &rect);
	globalCursor.x = globalCursor.y = rect.right / 2;
}

void Camera::Rotate(float degrees)
{
	//adding the rotation
	m_camera_rotation += XMConvertToRadians(degrees);

	//calculating the angle
	m_dx = sin(m_camera_rotation);
	m_dz = cos(m_camera_rotation);

	m_position = XMVectorSet(m_x, m_y, m_z, 0.0f);
	m_lookat = XMVectorSet(m_x + m_dx, m_y, m_z + m_dz, 0.0f);
	m_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
}

void Camera::LookAtCursorPos(HWND hWnd)
{
	//get the size of the window
	this->hWnd = hWnd;
	RECT rect;
	GetClientRect(hWnd, &rect);

	//get the cursor position on the screen
	POINT localCursor;
	GetCursorPos(&localCursor);

	//get the cursor position relative to the window size (does not work outside the window)
	ScreenToClient(hWnd, &localCursor);

	//if the local x position is bigger than the last position (global) then rotate the camera by
	if (localCursor.x > globalCursor.x)
		Rotate(localRotation = (localCursor.x - globalCursor.x) / sensitivity);
	else if (localCursor.x < globalCursor.x)
		Rotate(localRotation = -((globalCursor.x - localCursor.x) / sensitivity));

	//update rotation
	globalRotation += localRotation;

	//update position
	globalCursor = localCursor;


}

void Camera::windowResized()
{
	// if window resized regather the window size
	RECT rect;
	GetClientRect(hWnd, &rect);
	globalCursor.x = globalCursor.y = rect.right / 2;

}

void Camera::ResetView()
{
	//does not work
	m_position = XMVectorSet(0, 0, -.5f, 0.0f);
	m_lookat = XMVectorSet(0, 0, 0, 1.0f);
	m_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_dx = m_dy = m_dz = m_camera_rotation = m_x = m_y = m_z = 0;

	windowResized();
}

void Camera::StrafeX(float distanceX)
{
	XMFLOAT4 crossProd;
	
	//cross product between the forward position and the up position
	XMStoreFloat4(&crossProd, XMVector3Cross(XMVector3Normalize(m_position - m_lookat), XMVECTOR{ 0.0f,1.0f + abs(m_y),0.0f }));

	//updating the position
	m_x += crossProd.x * distanceX;

	//setting the position
	m_position = XMVectorSet(m_x, m_y, m_z, 0.0f);

}

void Camera::StrafeZ(float distanceZ)
{
	XMFLOAT4 crossProd;

	//cross product between the forward position and the up position
	XMStoreFloat4(&crossProd, XMVector3Cross(XMVector3Normalize(m_position - m_lookat), XMVECTOR{ 0.0f,1.0f + abs(m_y),0.0f }-m_position));

	//updating the position
	m_z += crossProd.z * distanceZ;

	//setting the position
	m_position = XMVectorSet(m_x, m_y, m_z, 0.0f);

}


void Camera::MoveUpDown(float distance)
{
	m_y += m_dz * distance;
	m_z += m_dy * distance;
	m_position = XMVectorSet(m_x, m_y, m_z, 0.0f);

}

void Camera::MoveForwardBackward(float distance)
{
	m_x += m_dx * distance;
	m_z += m_dz * distance;
	m_position = XMVectorSet(m_x, m_y, m_z, 0.0f);

}

void Camera::MoveLeftRight(float distance)
{
	m_x += m_dz * distance;
	m_y += m_dy * distance;
	m_position = XMVectorSet(m_x, m_y, m_z, 0.0f);
}




void Camera::UpdateLookAt(XMFLOAT3 vector)
{
	m_lookat = XMVectorSet(vector.x, vector.y, vector.z, 0);
}

float Camera::GetX()
{
	return m_x;
}

float Camera::GetY()
{
	return m_y;
}

float Camera::GetZ()
{
	return m_z;
}

void Camera::OrbitAroundPointXZ(XMFLOAT2 pointXZ, float Radius)
{
	//Rotating the camera around a given point and a given distance (radius) with 0.01 and saving it in degrees variable
	m_position = XMVectorSet(pointXZ.x+(cos(degrees += 0.01f) * Radius), m_y, pointXZ.y+(sin(degrees += 0.01f) * Radius), 0.0f);
}

XMMATRIX Camera::GetViewMatrix()
{
	return XMMatrixLookAtLH(m_position, m_lookat, m_up);
}
