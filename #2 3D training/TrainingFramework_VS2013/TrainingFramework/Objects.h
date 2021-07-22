#pragma once
#include "Utilities\utilities.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "CameraLookAt.h"
class Objects
{
private:
	GLuint m_vboId;
	GLuint m_iboId;
	GLuint m_textureId;
	Vector3 m_scale;
	Vector3 m_pos;
	Vector3 m_rot;
	Shaders *m_shaders;
	Texture *m_text;
	Models *m_model;
public:
	int Init(Vector3 _pos,Vector3 _rot,Vector3 _scale, Shaders* _shader,Texture* _text,Models* _model );
	void Draw(ESContext *esContext); 
	void DrawObj();
	void DrawCube();
	Matrix GetWorldMatrix(bool _forward);
	Objects();
	~Objects();
};

