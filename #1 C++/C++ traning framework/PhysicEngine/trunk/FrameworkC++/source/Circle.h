#pragma once
#include <math.h>
#include "Object.h"
class Circle :
	public Object
{
private:
	float m_radius;

public:
	virtual void Render();
	Circle(float x = 0, float y = 0, float mass = 1, float velocity = 0, float radius = 50);
	virtual void infor();
	virtual bool mouseCheck(int x, int y);
	virtual vector<float> getData();
	virtual ~Circle();
	virtual int shape();
	virtual void Update(float x, float y);
};

