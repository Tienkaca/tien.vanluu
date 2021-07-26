#pragma once
#include "Objects.h"
class FireObject :
	public Objects
{
private: 
	GLint m_uniDisplacementMapText;
	GLint m_uniFireText;
	GLint m_uniMaskText; 
	GLint m_uniUtime;

public:
	FireObject();
	~FireObject();
	virtual int Init(Vector3 _pos, Vector3 _rot, Vector3 _scale, Shaders* _shader, std::vector<Texture*> _texts, int* textArray, int textCount, Models* _model);
	virtual void Draw();
};

