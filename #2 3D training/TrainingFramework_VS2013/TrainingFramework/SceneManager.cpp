#include "stdafx.h"
#include "SceneManager.h"

SceneManager* SceneManager::ms_Instance = NULL;
SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}
int SceneManager::Init()
{
	int re;
	m_RMInstance = ResourceManager::GetInstance();
	char* SM = "../Resources/RMSM/SM.txt";
	FILE *file;
	file = fopen(SM, "r");
	if (!file)
		std::cout << "SceneManager::Init:Can not open this file" << std::endl;
	else
		std::cout << "SceneManager::Init:File is opened" << std::endl;
	int count;
	char buffer[255];
	fscanf(file,"#Cameras: %d\n",&count);
	for (int i = 0; i < count; i++)
	{
		int camId;
		fscanf(file, "ID %d\n", &camId);
		Vector3 posCam;
		fscanf(file, "POSITION %f %f %f\n", &posCam.x,&posCam.y,&posCam.z);
		Vector3 targetCam;
		fscanf(file, "TARGET %f %f %f\n", &targetCam.x, &targetCam.y, &targetCam.z);
		Vector3 up;
		fscanf(file, "UP %f %f %f\n",&up.x,&up.y,&up.z);
		float fov;
		fscanf(file, "FOVY %f\n",&fov);
		float nearPlane;
		fscanf(file, "NEAR %f\n", &nearPlane);
		float farPlane;
		fscanf(file, "FAR %f\n", &farPlane);
		float mSpeed;
		fscanf(file, "MOVE_SPEED %f\n", &mSpeed);
		float rSpeed;
		fscanf(file, "ROTATE_SPEED %f\n", &rSpeed);
		CameraLookAt::GetInstance()->Init(posCam, targetCam, up, fov, nearPlane, farPlane,mSpeed,rSpeed);
	}
	fscanf(file, "#Objects: %d\n", &count);
	for (int i = 0; i < count; i++)
	{
		Objects *O = new Objects;
		int OId;
		fscanf(file, "ID %d %s\n", &OId, &buffer);
		int modelId;
		fscanf(file, "MODEL %d\n", &modelId);
		int textCount,textId[8];
		fscanf(file, "TEXTURES %d\n", &textCount);
		for (int i = 0; i < textCount; i++)
		{
			fscanf(file, "TEXTURE %d\n", &textId[i]);
		}
		int cubeTextId;
		fscanf(file, "CUBETEXTURES %d\n", &cubeTextId);
		int shaderId;
		fscanf(file, "SHADER %d\n", &shaderId);
		int lightId;
		fscanf(file, "LIGHTS %d\n", &lightId);
		Vector3 pos;
		fscanf(file, "POSITION %f %f %f\n", &pos.x, &pos.y, &pos.z);
		Vector3 rot;
		fscanf(file, "ROTATION  %f %f %f\n", &rot.x, &rot.y, &rot.z);
		Vector3 scale;
		fscanf(file, "SCALE %f %f %f\n", &scale.x, &scale.y, &scale.z);
		if (textCount)
			re = O->Init(pos, rot, scale, m_RMInstance->mp_shaders.at(shaderId), m_RMInstance->mp_texture2D.at(textId[0]), m_RMInstance->mp_models.at(modelId));
		// chu y textId dong ben tren moi chi lay gia tri textId cua 1 texture
		else if (cubeTextId)
			re = O->Init(pos, rot, scale, m_RMInstance->mp_shaders.at(shaderId), m_RMInstance->mp_cubeTexture2D.at(cubeTextId), m_RMInstance->mp_models.at(modelId));

		m_objects.push_back(O);
	}
	return re;
}
void SceneManager::Draw(ESContext *esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < m_objects.size(); i++)
	{
		m_objects.at(i)->Draw(esContext);
	}
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void SceneManager::CreateInstance()
{
	if (ms_Instance == NULL)
		ms_Instance = new SceneManager;
}
SceneManager* SceneManager::GetInstance()
{
	return ms_Instance;
}
void SceneManager::DestroyInstance()
{
	if (ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = NULL;
	}
}