#include "stdafx.h"
#include "CameraLookAt.h"

CameraLookAt* CameraLookAt::ms_Instance = NULL;
CameraLookAt::CameraLookAt()
{
	m_pos.x = 0;		m_pos.y = 0;		m_pos.z = 0;
	m_target.x = 0;		m_target.y = 0;		m_target.z = 1;
	m_up.x = 0;			m_up.y = 1;			m_up.z = 0;
	m_mspeed = PI;
	m_rspeed = PI;
	m_P.SetPerspective(PI/2, Globals::screenWidth / Globals::screenHeight, 0.1, 500);
}

CameraLookAt::~CameraLookAt()
{
}
void CameraLookAt::Init(Vector3 _pos, Vector3 _target, Vector3 _up, float _FOVY, float _near, float _far, float _mspeed, float _rspeed)
{
	std::cout << "CameraLookAt::Init:\n";
	m_pos = _pos;
	std::cout <<"POS:"<< m_pos.x << m_pos.y << m_pos.z << "\n";
	m_target = _target;
	std::cout <<"TARGET:"<< m_target.x << m_target.y << m_target.z << "\n";
	m_up = _up;
	std::cout <<"UP:"<< m_up.x << m_up.y << m_up.z << "\n";
	m_mspeed = _mspeed;
	std::cout <<"MSPEED"<< m_mspeed << "\n";
	m_rspeed = _rspeed;
	std::cout <<"RSPEED"<< m_rspeed << "\n";
	m_P.SetPerspective(_FOVY, Globals::screenWidth / Globals::screenHeight, _near, _far);

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
	
	//P.SetPerspective(FOVY, Globals::screenWidth / Globals::screenHeight, NEARPLANE, FARPLANE);
	Matrix VP = GetViewMatrix()*m_P;
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
	Vector3 dz = -(m_pos - m_target).Normalize()*_dt*m_mspeed;
	Vector3 zaxis = (m_pos - m_target).Normalize();
	Vector3 xaxis = (m_up.Cross(zaxis).Normalize());
	Vector3 dx = xaxis*_dt*m_mspeed;
	float da = _dt*m_rspeed;
	switch (mp_signal)
	{
	case 'W': // phim w
		MoveZ(dz);
		std::cout << "phim w\n";
		break;
	case 'S': //phim s
		MoveZ(-dz);
		break;
	case 'A': // phim w
		MoveX(-dx);
		break;
	case 'D': //phim s
		MoveX(dx);
		break;
	case VK_UP: //phim mui ten len
		SetRotX(da);
		break;
	case VK_DOWN: // phim mui ten duoi
		SetRotX(-da);
		break;
	case VK_LEFT: // phim mui ten trai
		SetRotY(da);
		break;
	case VK_RIGHT: //mui ten sang phai
		SetRotY(-da);
		break;
	default:
		break;
	}
}
