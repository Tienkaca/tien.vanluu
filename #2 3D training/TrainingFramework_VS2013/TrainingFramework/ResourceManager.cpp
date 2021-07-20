#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::ms_Instance = NULL;
ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	for (int i = 0; i < mp_texture2D.size(); i++)
	{
		delete mp_texture2D.at(i);
	}
	for (int i = 0; i < mp_models.size(); i++)
	{
		delete mp_models.at(i);
	}
	for (int i = 0; i < mp_cubeTexture2D.size(); i++)
	{
		delete mp_cubeTexture2D.at(i);
	}
	for (int i = 0; i < mp_shaders.size(); i++)
	{
		delete mp_shaders.at(i);
	}
}
void ResourceManager::CreateInstance()
{
	if (ms_Instance == NULL)
		ms_Instance = new ResourceManager;
}
ResourceManager* ResourceManager::GetInstance()
{
	return ms_Instance;
}
void ResourceManager::DestroyInstance()
{
	if (ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = NULL;
	}
}
void ResourceManager::Init()
{
	char* RM = "../Resources/RMSM/RM.txt";
	FILE *file;
	file = fopen(RM, "r");
	if (!file)
		std::cout << "ResourceManager::Init:Can not open this file" << std::endl;
	else
		std::cout << "ResourceManager::Init:File is opened" << std::endl;
	int count;
	char buffer[255];
	fscanf(file, "#Models: %d\n", &count);
	for (int i = 0; i < count; i++)
	{
		Models *Mdl = new Models;
		fscanf(file, "ID %d\n", &Mdl->m_id);
		fscanf(file, "FILE %s\n", &Mdl->m_file);
		mp_models.push_back(Mdl);
		//std::cout << Mdl->m_id << "\n";
		//std::cout << Mdl->m_file << "\n";
	}
	fscanf(file, "#2D Textures: %d\n", &count);
	for (int i = 0; i < count; i++)
	{
		Texture *Txt = new Texture;
		Txt->mp_isCubeTexture = 0;
		fscanf(file, "ID %d\n", &Txt->m_id);
		//std::cout << Txt->m_id << "\n";
		fscanf(file, "FILE %s\n", &Txt->m_file);
		//std::cout << Txt->m_file << "\n";
		fscanf(file, "WRAP %s\n", &Txt->m_wrap);
		//std::cout << Txt->m_wrap << "\n";
		fscanf(file, "FILTER %s %s\n", &Txt->m_filter1, &Txt->m_filter2);
		//std::cout << Txt->m_filter1 << "\t" << Txt->m_filter2 << "\n";
		mp_texture2D.push_back(Txt);
	}
	fscanf(file, "#Cube Textures: %d\n", &count);
	for (int i = 0; i < count; i++)
	{
		Texture *Cube = new Texture;
		Cube->mp_isCubeTexture = 1;
		fscanf(file, "ID %d\n", &Cube->m_id);
		//std::cout << Cube->m_id << "\n";
		fscanf(file, "FILE %s\n", &Cube->m_file);
		//std::cout << Cube->m_file << "\n";
		fscanf(file, "WRAP %s\n", &Cube->m_wrap);
		//std::cout << Cube->m_wrap << "\n";
		fscanf(file, "FILTER %s %s\n", &Cube->m_filter1, &Cube->m_filter2);
		//std::cout << Cube->m_filter1 << "\t" << Cube->m_filter2 << "\n";
		mp_cubeTexture2D.push_back(Cube);
	}
	fscanf(file, "#Shaders: %d\n", &count);
	for (int i = 0; i < count; i++)
	{
		int n;
		Shaders *Sd = new Shaders;
		fscanf(file, "ID %d\n", &Sd->id);
		//std::cout << Sd->id << "\n";
		fscanf(file, "VS %s\n", &Sd->fileVS);
		//std::cout << Sd->fileVS << "\n";
		fscanf(file, "FS %s\n", &Sd->fileFS);
		//std::cout << Sd->fileFS << "\n";
		fscanf(file, "STATES %d\n", &n);
		//std::cout << n << "\n";
		for (int j = 0; j < n; j++)
		{
			fscanf(file, "%s %d\n", &buffer, &Sd->state[i]);
				//std::cout << buffer << "\t" << Sd->state[i] << "\n";
		}
		mp_shaders.push_back(Sd);
	}
}