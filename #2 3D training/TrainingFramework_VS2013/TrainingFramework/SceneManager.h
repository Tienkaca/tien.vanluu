#pragma once
#include "Object.h"
#include "ResourceManager.h"
#include "CameraLookAt.h"
class SceneManager
{
private:
	std::vector<Object*> m_objects;

public:
	void Init();
	SceneManager();
	~SceneManager();
};

