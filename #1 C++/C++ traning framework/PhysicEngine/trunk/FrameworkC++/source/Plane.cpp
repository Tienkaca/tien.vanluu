#include "Plane.h"



Plane::Plane():Object(1,1,1000,0),m_planeWidth(SCREEN_W -2), m_planeHight(SCREEN_H -2)
{
	
}


Plane::~Plane()
{
}

void Plane::Render()
{
	VideoDriver::GetInstance()->DrawRect(m_x, m_y, m_planeWidth, m_planeHight);
}

 vector<float> Plane::getData()
{
	vector<float> temp ;
	temp.push_back(m_x);
	temp.push_back(m_y);
	temp.push_back(m_x+m_planeWidth);
	temp.push_back(m_y+m_planeHight);
	return temp;
	cout << "PlaneGetData: " << temp[0] << "\t" << temp[1] << "\t" << temp[2] << "\t" << temp[3] << "\n";
}
 int Plane::shape()
 {
	 return 5;
 }
 void Plane::Update(float x, float y)
 {
 
 }
void Plane::setDeltaS(float vx, float vy)
 {
	m_deltaX = 0;
	m_deltaY = 0;
 }