#pragma once
#include <iostream>
#include <string.h>
#include "Utilities\utilities.h"
#include "Vertex.h"
class Models
{
public:
	GLuint m_vboId;
	GLuint m_iboId;
	int m_nrVertices;
	int m_nrIndices;
	int m_id;
	char m_file[255];
	void LoadModel(Vertex* &verticeData, int* &indiceData, bool isMultiText);
	void Init(bool isMultiText);
	Models();
	~Models();
};

