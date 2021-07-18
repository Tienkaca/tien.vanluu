#pragma once
#include "Object.h"
class Rectangles :
	public Object
{
	float m_width;
	float m_hight;
public:
	Rectangles(float x = 100, float y = 100, float mass =1, float velocity = 1, float width = 100, float hight =100);
	virtual ~Rectangles();
	virtual void Render();
	virtual void infor();
	virtual bool mouseCheck(int x, int y);
	virtual vector<float> getData();
	virtual int shape();
	virtual void Update(float x, float y);
};

