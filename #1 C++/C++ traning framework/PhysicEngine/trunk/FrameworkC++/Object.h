#pragma once
#include "videoDriver.h"
#include "esUtil.h"
#include "iostream"
#include <vector>
using namespace std;
class Object
{
 protected:
	 bool m_planeCollis;
	 bool m_collis;
	 float m_collisArg;
	bool m_mouseMovable;
	bool m_gravityAble;
	bool m_forceAble;
	float m_mouseOffsetX;
	float m_mouseOffsetY;
	float m_deltaX;
	float m_deltaY;
	float m_x;
	float m_y;
	float m_mass;
	float m_velocity;;
	float m_k;
public:

	bool isCollis();
	bool isPlaneCollis();
	void setCollis();
	void resetCollis();
	void setMouseMovable();
	bool mouseMovable();
	void resetMouseMovable();
	void setGravityAble();
	void resetGravityAble();
	void setForceAble();
	void resetForceAble();
	bool forceAble();
	void setCollisArg(float a);
	float calAngle(float x, float y);
	float Object::checkArg(int arg);
	void setPlaneCollis();
	void resetPlaneCollis();
	float getY();
	Object(float x = 0, float y = 0, float mass= 0, float velocity = 0);
	float getMass();
	vector<float>  getDeltaS();
	virtual void setDeltaS(float vx, float vy);
	virtual ~Object();
	virtual void Render();
	virtual void Update(float x, float y);
	virtual void infor();
	virtual bool mouseCheck(int x, int y);
	virtual vector<float> getData();
	virtual int shape();

};

