#pragma once
#include "Object.h"
class Plane :
	public Object
{
private:
	int m_planeWidth;
	int m_planeHight;
public:
	virtual void Render();
	virtual vector<float> getData();
	virtual int shape();
	virtual void Update(float x, float y);
	virtual void setDeltaS(float vx, float vy);
	Plane();
	~Plane();
};

