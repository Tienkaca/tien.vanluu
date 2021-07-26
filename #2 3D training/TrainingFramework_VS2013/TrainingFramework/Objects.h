#pragma once
#include "Utilities\utilities.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "CameraLookAt.h"
class Objects
{
protected:
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
	GLint m_uniTextureLoc;
public:
	virtual int Init(Vector3 _pos, Vector3 _rot, Vector3 _scale, Shaders* _shader, std::vector<Texture*> _texts, int* textArray, int textCount, Models* _model);
	virtual void Draw();
	Matrix GetWorldMatrix(bool _forward);
	Objects();
	~Objects();
};

