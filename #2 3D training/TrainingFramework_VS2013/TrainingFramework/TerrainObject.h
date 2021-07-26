#pragma once
#include "Objects.h"
class TerrainObject : public Objects
{
private:
	GLint m_textsLoc[5];
	GLint m_uniY;
public:
	virtual int Init(Vector3 _pos, Vector3 _rot, Vector3 _scale, Shaders* _shader, std::vector<Texture*> _texts, int* textArray, int textCount, Models* _model);
	virtual void Draw();
	void InitHeightMap();
	TerrainObject();
	~TerrainObject();
};

