#include "stdafx.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}
void Init()
{
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
		Vector3 posCam;
		fscanf(file, "POSITION %f %f %f\n", &posCam.x,&posCam.y,&posCam.z);
		Vector3 targetCam;
		//fscanf(file,"TARGET %f %f %f\n",&tar)
	}

}