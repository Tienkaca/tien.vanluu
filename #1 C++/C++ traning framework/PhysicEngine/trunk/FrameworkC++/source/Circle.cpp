#include "Circle.h"



Circle::Circle(float x, float y, float mass, float velocity, float radius) : Object(x, y, mass, velocity), m_radius(radius)
{
}
void Circle::Render()
{
	VideoDriver::GetInstance()->DrawCircle(m_x, m_y, m_radius);
}
void Circle::infor()
{
	std::cout << "Position:" << m_x << "\t" << m_y << std::endl;
	std::cout << "Radius:" << m_radius << std::endl;
	std::cout << "Mass:" << m_mass << std::endl;
	std::cout << "Velocity:" << m_velocity << std::endl;
}
Circle::~Circle()
{
	
}



bool Circle::mouseCheck(int x, int y)
{
	int delta = (int)sqrt((m_x - x)*(m_x -x) + (m_y - y)*(m_y - y));
	if (delta < m_radius)
	{
		m_mouseOffsetX = m_x - x;
		m_mouseOffsetY = m_y - y;
		//cout << "MOUSE CHECK CIRCLE";
		return true;
	}	
	else 
	{
		return false;
	}
}
vector<float> Circle::getData()
{
	vector<float> temp ;
	temp.push_back(m_x);
	temp.push_back(m_y);
	temp.push_back(m_radius);
	
	return temp;	
}

int Circle::shape()
{
	return 3;
}
void Circle::Update(float x, float y)
{
	
		if (m_mouseMovable)
		{
			m_x = x + m_mouseOffsetX;
			m_y = y + m_mouseOffsetY;
			//cout << "mouse\n";
			
		}
		else
		{
			if ((m_deltaX || m_deltaY))
			{
				static bool stsCollis = 1;
				if (m_planeCollis && stsCollis)
				{
					if (m_collisArg == PI/2 || m_collisArg == -PI/2)
					{
						m_deltaX = -m_deltaX;
					}
					else if (m_collisArg == 0 || m_collisArg == PI)
					{
						m_deltaY = -m_deltaY;
					}
					stsCollis = 0;
				}
				if (!m_planeCollis)
				{
					stsCollis = 1;
				}
				m_x = m_x + m_deltaX / m_k;
				m_y = m_y + m_deltaY / m_k;
			}
			//else if (m_gravityAble || !(m_deltaX && m_deltaY))
			//{
			//	//gravity and collision
			//	m_deltaX = 0;
			//	m_deltaY = GRAVITY;
			//	if (m_collis)
			//	{
			//		//cout << "Circle::Update: COLLISION\n";
			//		m_deltaX = 0;
			//		m_deltaY = 0;
			//	}
			//	// if colission 
			//	m_x = m_x + m_deltaX / m_k;
			//	m_y = m_y + m_deltaY / m_k;
			//}
		}
	
}