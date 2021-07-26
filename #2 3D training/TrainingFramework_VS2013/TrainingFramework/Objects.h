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
	Texture *m_textCube;
	std::vector<Texture*> m_texts;
	Models *m_model;
public:
	bool mp_isCube;
	bool mp_isMutiText;
	int Init(Vector3 _pos,Vector3 _rot,Vector3 _scale, Shaders* _shader,Texture* _text,Models* _model );
	int Init(Vector3 _pos, Vector3 _rot, Vector3 _scale, Shaders* _shader, std::vector<Texture*> _texts, int* textArray, int textCount, Models* _model);
	void Draw(ESContext *esContext); 
	void DrawObj();
	void DrawCube();
	Matrix GetWorldMatrix(bool _forward);
	Objects();
	~Objects();
};

