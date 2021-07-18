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
using namespace std;
Vector3 scale(0.2, 0.2, 0.2);
Vector4 rota(0, 0, 1, 1);
Vector4 posi(0, 0 ,1, 1);
//Vector3 scale2(0.5, 0.5, 0.5);
//Vector4 rota2(0, 0, 0, 1);
//Vector4 posi2(0.5, 0, 0.9, 1);
Object Obj(scale,posi,rota,"../Resources/Models/Woman1.nfg", "../Resources/Textures/Woman1.tga", "../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
//Object Obj2(scale2, posi2, rota2, "../Resources/Models/Woman2.nfg", "../Resources/Textures/Woman2.tga", "../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
int Init ( ESContext *esContext )
{
	
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

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed && key == 'q')
		std::cout << "hahaha";
}

void CleanUp()
{
	CameraLookAt::GetInstance()->DestroyInstance();
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;
	CameraLookAt::GetInstance()->CreateInstance();
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

