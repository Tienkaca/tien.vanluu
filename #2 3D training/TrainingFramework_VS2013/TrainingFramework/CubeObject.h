#pragma once
#include "Objects.h"
class CubeObject :
	public Objects
{
private:
	GLint m_uniCubeTextLoc;
public:
	CubeObject();
	~CubeObject();
	virtual int Init(Vector3 _pos, Vector3 _rot, Vector3 _scale, Shaders* _shader, std::vector<Texture*> _texts, int* textArray, int textCount, Models* _model);
	virtual void Draw();
};

