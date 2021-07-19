#pragma once
#include <Vector>
#include <iostream>
#include <string.h>
#include "Texture.h"
#include "Shaders.h"
#include "Models.h"
class ResourceManager
{
public:
	std::vector<Texture*> mp_texture2D;
	std::vector<Texture*> mp_cubeTexture2D;
	std::vector<Shaders*> mp_shaders;
	std::vector<Models*> mp_models;
	void Init();
	ResourceManager();
	~ResourceManager();
	static void CreateInstance();
	static ResourceManager* GetInstance();
	static void DestroyInstance();
	static ResourceManager *ms_Instance;
};

