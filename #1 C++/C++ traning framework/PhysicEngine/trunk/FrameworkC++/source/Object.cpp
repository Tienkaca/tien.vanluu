#include "Object.h"



Object::Object(float x, float y, float mass, float velocity)
{
	m_mouseMovable = 0;
	m_gravityAble = 1;
	m_forceAble = 0;
	m_planeCollis = 0;
	m_x = x;
	m_y = y;
	m_mass = mass;
	m_velocity = velocity;
	m_mouseOffsetX = 0;
	m_mouseOffsetY = 0;
	m_collis = 0;
	m_deltaX = 0;
	m_deltaY = GRAVITY;
	m_k = 50;
}
void Object::Update(float x, float y)
{
	
}
void Object::infor()
{ 
	std::cout<<"Position:"<< m_x<<"\t"<<m_y<<std::endl;
	std::cout << "Mass:" << m_mass <<  std::endl;
	std::cout << "Velocity:" << m_velocity << std::endl;
}
Object::~Object()
{
}

void Object::Render()
{
	
}
bool Object::mouseCheck(int x, int y)
{	
	
	return 0;
}

void Object::resetMouseMovable()
{
	m_mouseMovable = 0;
	
}

void Object::setMouseMovable()
{
	m_mouseMovable = 1;
	//m_forceAble = 0;
	//m_gravityAble = 0;
}
void Object::setGravityAble()
{
	//m_mouseMovable = 0;
	//m_forceAble = 0;
	m_gravityAble = 1;
}
void Object::resetGravityAble()
{
	m_gravityAble = 0;
}
void Object::setForceAble()
{
	//m_mouseMovable = 0;
	m_forceAble =	1;
	//m_gravityAble = 0;
}
void Object::resetForceAble()
{
	m_forceAble = 0;
}
bool Object::mouseMovable()
{
	return m_mouseMovable;
}
void Object::setDeltaS(float vx, float vy)
{
	m_deltaX = vx;
	m_deltaY = vy;
}
vector<float> Object::getData()
{
	vector<float> t;
	return t;
	
}
bool Object::isCollis()
{
	return m_collis;
}
void Object::setCollis()
{
	m_collis = true;
}
void Object::resetCollis()
{
	m_collis = false;
}

bool Object::forceAble()
{
	return m_forceAble;
}
int Object::shape()
{
	return 1;
}
void Object::setCollisArg(float a)
{
	m_collisArg = a;
}

float Object::checkArg(int arg)
{
	switch (arg)
	{
		case 1:
			return 3 * PI / 4;
		case 2:
			return PI / 2;
		case 3:
			return PI / 3;
		case 4:
			return 0;
		case 5:
			return -PI / 4;
		case 6:
			return -PI / 2;
		case 7:
			return -3 * PI / 4;
		case 8:
			return -PI;
	}
}

float Object::calAngle(float x, float y)
{
	float d = sqrt(x*x + y*y);
	if (y <= 0)    //he truc toa do nguoc
	{
		return acos(x / d);
	}
	else
		return (-acos(x / d));
}
void Object::setPlaneCollis()
{
	 m_planeCollis = 1;
}
void Object::resetPlaneCollis()
{
	m_planeCollis = 0;
}
bool Object::isPlaneCollis()
{
	return m_planeCollis;
}
float Object::getY()
{
	return m_y;
}
float Object::getMass()
{
	return m_mass;
}
vector<float> Object::getDeltaS()
{
	vector<float> temp;
	temp.push_back(m_deltaX);
	temp.push_back(m_deltaY);
	return temp;
}
bool Object::IsFalling()
{
	return m_gravityAble;
}