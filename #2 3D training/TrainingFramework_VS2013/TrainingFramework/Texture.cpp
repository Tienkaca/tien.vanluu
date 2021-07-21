#include "stdafx.h"
#include "Texture.h"


Texture::Texture()
{
	m_id = 0;
	mp_isCubeTexture = 0;
}


Texture::~Texture()
{
}

void Texture::Init()
{
	
}
void Texture::InitObj()
{
	int w, h, bpp;
	glGenTextures(1, &m_textId);
	glBindTexture(GL_TEXTURE_2D, m_textId);
	char *imageData = LoadTGA(m_file, &w, &h, &bpp);
	if (bpp == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}
	delete[] imageData;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);*/
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::InitCube()
{
	int w, h, bpp;
	std::vector<std::string> files = {
		" ../Resources/Textures/left.tga",
		" ../Resources/Textures/right.tga",
		" ../Resources/Textures/top.tga",
		" ../Resources/Textures/bottom.tga",
		" ../Resources/Textures/front.tga",
		" ../Resources/Textures/back.tga"
	};
	glGenTextures(1, &m_textId);
	glBindTexture(GL_TEXTURE_CUBE_MAP,m_textId);
	for (int i = 0; i<6; i++)
	{
		char *imageData = LoadTGA(files[i].c_str(), &w, &h, &bpp);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0,
			GL_RGB,
			w,
			h,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			imageData);
		delete[] imageData;
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}