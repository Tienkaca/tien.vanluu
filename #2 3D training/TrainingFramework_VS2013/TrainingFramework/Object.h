#pragma once
#include <iostream>
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Camera.h"
#include "CameraLookAt.h"
class Object
{
protected:
	GLuint m_vboId;
	GLuint m_iboId;
	GLuint m_textureId;
	Shaders m_shaders;
	Vector3 m_scale;
	Vector3 m_pos;
	Vector3 m_rot;
	int m_nrVertices;
	int m_nrIndices;
	char* m_nfgId;
	char* m_tdaId;
	char* m_VSShaderId;
	char* m_FTShaderId;
public:
	int Init();
	void InitData(Vertex* &verticeData, int* &indiceData);
	void Draw(ESContext *esContext);
	Matrix GetWorldMatrix(bool _forward);
	Object(Vector3 _scale, Vector3 _pos, Vector3 _rot, char* _nfgId = 0, char* _tgaId = 0, char* _VSShaderId = 0, char* _FTShaderId = 0 );
	~Object();
};

