#pragma once
#include <string.h>
#include <iostream>
class Texture
{
public:
	int m_id;
	char m_file[255];
	char m_wrap[255];
	char m_filter1[128];
	char m_filter2[128];
	bool mp_is2DTexture;
	void initData();
	Texture();
	~Texture();
};

