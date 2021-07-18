#include "stdafx.h"
#include "CameraLookAt.h"

CameraLookAt* CameraLookAt::ms_Instance = NULL;
CameraLookAt::CameraLookAt()
{
	m_pos.x = 0;		m_pos.y = 0;		m_pos.z = 0;
	m_target.x = 0;		m_target.y = 0;		m_target.z = 1;
	m_up.x = 0;			m_up.y = 1;			m_up.z = 0;
}

CameraLookAt::~CameraLookAt()
{
}
void CameraLookAt::CreateInstance()
{
	if (ms_Instance == NULL)
		ms_Instance = new CameraLookAt;
}
CameraLookAt* CameraLookAt::GetInstance()
{
	return ms_Instance;
}
void CameraLookAt::DestroyInstance()
{
	if (ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = NULL;
	}
}
Matrix CameraLookAt::GetViewMatrix()
{
	Matrix V = GetTranMatrix(false)*GetRotMatrix(false)*GetScaleMatrix(false);
	return V;
}
Matrix CameraLookAt::GetWorldMatrix(bool _forward)
{
	if (_forward)
		return (GetScaleMatrix(true)*GetRotMatrix(true)*GetTranMatrix(true));
	else
		return (GetTranMatrix(false)*GetRotMatrix(false)*GetScaleMatrix(false));

}
Matrix CameraLookAt::GetViewPerspectiveMatrix()
{
	Matrix P;
	P.SetPerspective(FOVY, Globals::screenWidth / Globals::screenHeight, NEARPLANE, FARPLANE);
	Matrix VP = GetViewMatrix()*P;
	return VP;
}
Matrix CameraLookAt::GetRotMatrix(bool _forward)
{
	Vector3 zaxis = (m_pos - m_target).Normalize();
	Vector3 xaxis = (m_up.Cross(zaxis).Normalize());
	Vector3 yaxis = (zaxis.Cross(xaxis).Normalize());
	Matrix R;
	R.m[0][0] = xaxis.x;	R.m[0][1] = xaxis.y;	R.m[0][2] = xaxis.z;	R.m[0][3] = 0;
	R.m[1][0] = yaxis.x;	R.m[1][1] = yaxis.y;	R.m[1][2] = yaxis.z;	R.m[1][3] = 0;
	R.m[2][0] = zaxis.x;	R.m[2][1] = zaxis.y;	R.m[2][2] = zaxis.z;	R.m[2][3] = 0;
	R.m[3][0] = 0;			R.m[3][1] = 0;			R.m[3][2] = 0;			R.m[3][3] = 1;
	if (_forward)
		return R;
	else
		return (R.Transpose());
}
Matrix CameraLookAt::GetTranMatrix(bool _forward)
{
	Matrix T;
	if (_forward)
		T.SetTranslation(m_pos.x, m_pos.y, m_pos.z);
	else
		T.SetTranslation(-m_pos.x, -m_pos.y, -m_pos.z);
	return T;
}
Matrix CameraLookAt::GetScaleMatrix(bool _forward)
{
	Matrix S;
	if (_forward)
		return (S.SetScale(m_scale));
	else
		return (S.SetScale(1 / m_scale));
}
void CameraLookAt::SetRotY(float _angle)
{
	Vector3 zaxis = (m_pos - m_target).Normalize();
	Vector3 xaxis = (m_up.Cross(zaxis).Normalize());
	Vector3 yaxis = (zaxis.Cross(xaxis).Normalize());
	Vector4 LTarget(0, 0, -(m_pos - m_target).Length(), 1);
	Matrix Ry;
	Ry.SetRotationAngleAxis(_angle, yaxis.x, yaxis.y, yaxis.z);
	Vector4 LNTarget = LTarget * Ry;
	Vector4 WTarget = LNTarget*GetWorldMatrix(true);
	m_target.x = WTarget.x;
	m_target.y = WTarget.y;
	m_target.z = WTarget.z;
}
void CameraLookAt::SetRotX(float _angle)
{
	Vector3 zaxis = (m_pos - m_target).Normalize();
	Vector3 xaxis = (m_up.Cross(zaxis).Normalize());
	Vector4 LTarget(0, 0, -(m_pos - m_target).Length(), 1);
	Matrix Rx;
	Rx.SetRotationAngleAxis(_angle, xaxis.x, xaxis.y, xaxis.z);
	Vector4 LNTarget = LTarget * Rx;
	Vector4 WTarget = LNTarget*GetWorldMatrix(true);
	m_target.x = WTarget.x;
	m_target.y = WTarget.y;
	m_target.z = WTarget.z;
}
void CameraLookAt::MoveZ(Vector3 _dz)
{
	m_pos += _dz;
	m_target += _dz;
}
void CameraLookAt::MoveX(Vector3 _dx)
{
	m_pos += _dx;
	m_target += _dx;
}
void CameraLookAt::Update(float _dt)
{
	Vector3 dz = -(m_pos - m_target).Normalize()*_dt*SPEEDMOVE;
	Vector3 zaxis = (m_pos - m_target).Normalize();
	Vector3 xaxis = (m_up.Cross(zaxis).Normalize());
	Vector3 dx = xaxis*_dt*SPEEDMOVE;
	float da = _dt*SPEEDROT;
	char signal;
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
			MoveZ(dz);
			std::cout << "phim w\n";
			break;
		case 115: //phim s
			MoveZ(-dz);
			std::cout << "phim s\n";
			break;
		case 'a': // phim w
			MoveX(dx);
			std::cout << "phim a\n";
			break;
		case 'd': //phim s
			MoveX(-dx);
			std::cout << "phim d\n";
			break;
		case 72: //phim mui ten len
			SetRotX(da);
			std::cout << "phim len\n";
			break;
		case 80: // phim mui ten duoi
			SetRotX(-da);
			std::cout << "phim duoi\n";
			break;
		case 75: // phim mui ten trai
			SetRotY(da);
			std::cout << "phim trai\n";
			break;
		case 77: //mui ten sang phai
			SetRotY(-da);
			std::cout << "phim phai\n";
			break;
		default:
			break;
		}
	}
}
