#pragma once
#include <iostream>
#include "../Utilities/utilities.h" 
#include "defines.h"
#include <stdio.h>
#include <conio.h>
#include "Globals.h"
class Camera
{
private:
	Vector4 m_pos;
	Vector4 m_rot;
	float m_scale;
	
public:
	Camera();
	~Camera();
	Matrix GetRotMatrix(bool _forward);
	Matrix GetTranslateMatrix(bool _forward);
	Matrix GetScaleMatrix(bool _forward);
	Matrix GetWorldMatrix(bool _forward);
	Matrix GetWVPMatrix();
	void SetRotation(float _dx,float _dy, float _dz);
	void SetTranslation(float _dx,float _dy, float _dz);
	void Update();
	static void CreateInstance();
	static Camera* GetInstance();
	static void DestroyInstance();
protected:
	static Camera *ms_Instance;

};

