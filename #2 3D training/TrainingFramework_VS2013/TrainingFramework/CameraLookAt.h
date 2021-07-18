#pragma once
#include <iostream>
#include "Utilities\utilities.h"
#include "Globals.h"
#include "defines.h"
#include <conio.h>
class CameraLookAt
{
private:
	Vector3 m_up;
	Vector3 m_target;
	Vector3 m_pos;
	float	m_scale = 1;
	static CameraLookAt* ms_Instance;
public:
	void Update(float _dt);
	Matrix GetViewMatrix();
	Matrix GetViewPerspectiveMatrix();
	Matrix GetWorldMatrix(bool _forward);
	Matrix GetRotMatrix(bool _forward);
	Matrix GetTranMatrix(bool _forward);
	Matrix GetScaleMatrix(bool _forward);
	void SetRotY(float _angle);
	void SetRotX(float _angle);
	void MoveZ(Vector3 _dz);
	void MoveX(Vector3 _dx);
	CameraLookAt();
	~CameraLookAt();
	static void CreateInstance();
	static CameraLookAt* GetInstance();
	static void DestroyInstance();
};

