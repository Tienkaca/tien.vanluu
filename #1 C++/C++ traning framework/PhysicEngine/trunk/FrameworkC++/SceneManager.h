#pragma once
#include "Object.h"
#include <vector>
#include <stdio.h>
#include "esUtil.h"
#include "log.h"
#include "define.h"
#include "VideoDriver.h"
#include <crtdbg.h>
#include <iostream>
#include <string.h>
#include "Rectangles.h"
#include "Circle.h"
#include "Points.h"
#include "CollisionManager.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

class SceneManager
{
protected:
	
	std::vector<Object*> m_Objects;
	float m_mousePosX;
	float m_mousePosY;
	float m_deltaX;
	float m_deltaY;
	CollisionManager m_collis;
public:
	void Update();
	void UpdateDS();
	void AddObject(Object *object);
	void Init();
	void Render();
	void touchActionDown(int x, int y);
	void touchActionMove(int x, int y);
	void touchActionUp(int x, int y);
	void setMouseMovable(int x, int y);
	void resetMouseMovable();
	void getMousePosition(int x, int y);
	std::vector<Object*> getObjects();
	SceneManager();
	~SceneManager();


	static SceneManager *Instance;
	static void CreateInstance()
	{
		if(Instance == NULL)
		{
			Instance = new SceneManager;
		}
	}
	static SceneManager* GetInstance()
	{
		return Instance;
	}
	static void DestroyInstance()
	{
		if (Instance)
		{
			delete Instance;
			Instance = NULL;
		}
	}

};

