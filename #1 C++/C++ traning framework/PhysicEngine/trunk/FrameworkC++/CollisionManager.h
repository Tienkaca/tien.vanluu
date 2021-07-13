#pragma once
#include "Object.h"
#include "Plane.h"
#include "Circle.h"
#include "Rectangles.h"
#include <iostream>
#include <vector>
class CollisionManager
{
private:
	bool m_c[10][10];
	float m_e;
public:
	void updateCollision(std::vector<Object*> Objects);
	bool checkCollision(Object* O1, Object* O2);
	bool checkRectCirCollision( Object* R,  Object* C);
	bool checkRectRectCollision(Object* R1, Object* R2);
	bool checkCirCirCollision( Object* C1,  Object* C2);
	bool UpdatePlaneCollsion( Object* O,  Object* P);
	bool checkRectPlaneCollision(Object* R, Object* P);
	bool checkCirPlaneCollision(Object* C, Object* P);
	void setVelCollision(Object* O1, Object* O2);
	void updatem_c(std::vector<Object*> Objects);
	void setObjectCollis(std::vector<Object*> Objects);
	void checkm_c(int j, int size);
	void showm_c(int n);
	float dis(float x1,float  y1,float  x2,float  y2)
	{
		return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	}
	CollisionManager();
	~CollisionManager();
};

