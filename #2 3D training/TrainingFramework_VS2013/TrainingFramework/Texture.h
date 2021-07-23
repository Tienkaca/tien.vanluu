#pragma once
#include <string.h>
#include <iostream>
#include <vector>
#include "Utilities\utilities.h"
class Texture
{
public:
	GLuint m_textId;
	int m_id;
	char m_file[255];
	char m_wrap[255];
	char m_filter1[128];
	char m_filter2[128];
	bool mp_isCubeTexture;
	void InitObj(int itext);
	void InitCube();
	void Init(int itext);
	Texture();
	~Texture();
};

