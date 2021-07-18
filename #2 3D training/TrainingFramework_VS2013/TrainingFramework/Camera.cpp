#include "stdafx.h"
#include "Camera.h"

Camera* Camera::ms_Instance = NULL;
Camera::Camera()
{
	m_pos.x = 0; m_pos.y = 0; m_pos.z = 0; m_pos.w = 1;
	m_rot.x = 0; m_rot.y = 0; m_rot.z = 0; m_rot.w = 1;
	m_scale = 1;
}


Camera::~Camera()
{
}
void Camera::CreateInstance()
{
	if (ms_Instance == NULL)
		ms_Instance = new Camera;
}
Camera* Camera::GetInstance()
{
	return ms_Instance;
}
void Camera::DestroyInstance()
{
	if (ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = NULL;
	}
}
Matrix Camera::GetRotMatrix(bool _forward)
{
	Matrix  Rx, Ry, Rz, R;
	if (_forward)
	{
		Rx.SetRotationX(m_rot.x);
		Ry.SetRotationY(m_rot.y);
		Rz.SetRotationZ(m_rot.z);
		R = Rz*Rx*Ry;
	}
	else
	{
		Rx.SetRotationX(-m_rot.x);
		Ry.SetRotationY(-m_rot.y);
		Rz.SetRotationZ(-m_rot.z);
		R = Ry*Rx*Rz;
	}
	return R;
}
Matrix Camera::GetTranslateMatrix(bool _forward)
{
	Matrix translation;
	if (_forward)
		translation.SetTranslation(m_pos.x, m_pos.y, m_pos.z);		 //forward matrix
	else
		translation.SetTranslation( -m_pos.x, -m_pos.y, -m_pos.z);	 //inverse matrix
	return translation;
}
Matrix Camera::GetScaleMatrix(bool _forward)
{
	Matrix scale;
	if (_forward)
		scale.SetScale(m_scale);		 //forward matrix
	else
		scale.SetScale(1/m_scale);		 //inverse matrix
	return scale;
}
Matrix Camera::GetWorldMatrix(bool _forward)
{
	Matrix world;
	if (_forward)
		world = GetScaleMatrix(true)*GetRotMatrix(true)*GetTranslateMatrix(true);    //forward matrix
	else
		world = GetScaleMatrix(false)*GetTranslateMatrix(false)*GetRotMatrix(false); //inverse matrix
	return world;
}
Matrix Camera::GetWVPMatrix()
{
	Matrix WV = GetWorldMatrix(false);
	Matrix P;
	P.SetPerspective(1.0,(float)Globals::screenWidth/Globals::screenHeight,NEARPLANE, FARPLANE);
	Matrix WVP = WV*P;
	return WVP;
}
void Camera::SetRotation(float _dx, float _dy, float _dz)
{
	m_rot.x += _dx;
	m_rot.y += _dy;
	m_rot.z += _dz;
}
void Camera::SetTranslation(float _dx, float _dy, float _dz)
{
	m_pos.x += _dx;
	m_pos.y += _dy;
	m_pos.z += _dz;
}
void Camera::Update()
{
	Vector4 deltaMove(0, 0, DELTAMOVE, 0);
	Vector4 deltaMoveW = deltaMove*GetWorldMatrix(true);
	Vector4 deltaRotX(DELTAROT, 0, 0, 0);
	Vector4 deltaRotY(0,DELTAROT, 0, 0);
	Vector4 deltaRotXW = deltaRotX*GetWorldMatrix(true);
	Vector4 deltaRotYW = deltaRotY*GetWorldMatrix(true);
	static char signal = 0;
	if (kbhit())
	{
		signal = getch();
		if (signal == 224);
		{
			signal = getch();
			//printf("%i", signal);
		}
		switch (signal)
		{
		case 'w': // phim w
			m_pos += deltaMoveW;
			std::cout << "phim w\n";
			break;
		case 115: //phim s
			m_pos -= deltaMoveW;
			std::cout << "phim s\n";
			break;
		case 72: //phim mui ten len
			m_rot += deltaRotXW;
			std::cout << "phim len\n";
			break;
		case 80: // phim mui ten duoi
			m_rot -= deltaRotXW;
			std::cout << "phim duoi\n";
			break;
		case 75: // phim mui ten trai
			m_rot += deltaRotYW;
			std::cout << "phim trai\n";
			break;
		case 77: //mui ten sang phai
			m_rot -= deltaRotYW;
			std::cout << "phim phai\n";
			break;
		default:
			break;
		}
	}
}