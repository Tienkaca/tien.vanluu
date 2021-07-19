// TrainingFramework.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"

#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "Camera.h"
#include "Object.h"
#include "CameraLookAt.h"
#include "ResourceManager.h"
using namespace std;
Vector3 scale(0.2, 0.2, 0.2);
Vector3 rota(0, 0, 1);
Vector3 posi(0, 0 ,1);
//Vector3 scale2(0.5, 0.5, 0.5);
//Vector4 rota2(0, 0, 0, 1);
//Vector4 posi2(0.5, 0, 0.9, 1);
Object Obj(scale,posi,rota,"../Resources/Models/Woman1.nfg", "../Resources/Textures/Woman1.tga", "../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
//Object Obj2(scale2, posi2, rota2, "../Resources/Models/Woman2.nfg", "../Resources/Textures/Woman2.tga", "../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
int Init ( ESContext *esContext )
{
	ResourceManager::GetInstance()->Init();
	return ( Obj.Init());
	//glEnable(GL_DEPTH_TEST);
}

void Draw(ESContext *esContext)
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	
	Obj.Draw(esContext);
	glClear(GL_DEPTH_BUFFER_BIT);
	
}

void Update ( ESContext *esContext, float deltaTime )
{
	CameraLookAt::GetInstance()->Update(deltaTime);
}

void Key(ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch(key)
		{
		case 'W': // phim w
			CameraLookAt::GetInstance()->mp_signal = key;
			std::cout << "phim w\n";
			break;
		case 'S': //phim s
			CameraLookAt::GetInstance()->mp_signal = key;
			std::cout << "phim s\n";
			break;
		case 'A': // phim w
			CameraLookAt::GetInstance()->mp_signal = key;
			std::cout << "phim a\n";
			break;
		case 'D': //phim s
			CameraLookAt::GetInstance()->mp_signal = key;
			std::cout << "phim d\n";
			break;
		case VK_UP: //phim mui ten len
			CameraLookAt::GetInstance()->mp_signal = key;
			std::cout << "phim len\n";
			break;
		case VK_DOWN: // phim mui ten duoi
			CameraLookAt::GetInstance()->mp_signal = key;
			std::cout << "phim duoi\n";
			break;
		case VK_LEFT: // phim mui ten trai
			CameraLookAt::GetInstance()->mp_signal = key;
			std::cout << "phim trai\n";
			break;
		case VK_RIGHT: //mui ten sang phai
			CameraLookAt::GetInstance()->mp_signal = key;
			std::cout << "phim phai\n";
			break;
		default:
			CameraLookAt::GetInstance()->mp_signal = 0;
			break;
		}
	}
	else
	{
		CameraLookAt::GetInstance()->mp_signal = 0;
	}
}

void CleanUp()
{
	CameraLookAt::GetInstance()->DestroyInstance();
	ResourceManager::GetInstance()->DestroyInstance();
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;
	CameraLookAt::GetInstance()->CreateInstance();
	ResourceManager::GetInstance()->CreateInstance();
    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

