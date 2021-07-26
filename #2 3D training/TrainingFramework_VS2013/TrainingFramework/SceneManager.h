#pragma once
#include "Object.h"
#include "ResourceManager.h"
#include "CameraLookAt.h"
#include "ResourceManager.h"
#include "Objects.h"
#include "TerrainObject.h"
#include "CubeObject.h"
#include "FireObject.h"
class SceneManager
{
private:
	std::vector<Objects*> m_objects;
	ResourceManager *m_RMInstance;
public:
	int Init();
	void Draw(ESContext *esContext);
	SceneManager();
	~SceneManager();
	static void CreateInstance();
	static SceneManager* GetInstance();
	static void DestroyInstance();
	static SceneManager *ms_Instance;
};

