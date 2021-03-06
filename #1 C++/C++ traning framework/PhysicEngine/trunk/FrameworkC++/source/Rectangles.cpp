#include "Rectangles.h"



Rectangles::Rectangles(float x,float y,float mass,float velocity,float width,float hight): Object(x,y,mass,velocity), m_width(width), m_hight(hight)
{
	//std:: cout<< m_x<<"\t"<<m_x+ width<<"\t"<<m_y<<"\t"<<m_y+height<<"\n";
}


Rectangles::~Rectangles()
{
}

void Rectangles::Render()
{
	VideoDriver::GetInstance()->DrawRect(m_x, m_y, m_width,m_hight);

}
void Rectangles::infor()
{
	std::cout << "Position:" << m_x << "\t" << m_y << std::endl;
	std::cout << "Width, Height:" << m_width <<"\t"<<m_hight<< std::endl;
	std::cout << "Mass:" << m_mass << std::endl;
	std::cout << "Velocity:" << m_velocity << std::endl;

}


bool Rectangles::mouseCheck(int x, int y)
{
	if((m_x <= x && x <=(m_x + m_width)) && (m_y <=  y && y <= (m_y+ m_hight)) )
	{
		m_mouseOffsetX =  m_x - x;
		m_mouseOffsetY = m_y - y;
		//cout << "MOUSE CHECK RECT";
		return true;
	}
	else
		return false;
}
vector<float> Rectangles::getData()
{
	vector<float> temp;
	temp.push_back(m_x);
	temp.push_back(m_y);
	temp.push_back(m_x + m_width);
	temp.push_back(m_y + m_hight);
	return temp;
}

int Rectangles::shape()
{
	return 4;
}
void Rectangles::Update(float x, float y)
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
				if(m_planeCollis && stsCollis)
				{
					if (m_collisArg == 2 || m_collisArg == 6)
					{
						m_deltaX = -m_deltaX;
					}
					else if (m_collisArg == 8 || m_collisArg == 4)
					{
						m_deltaY = -m_deltaY;
					}
					stsCollis = 0;
				}
				if(!m_planeCollis)
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
			//		//cout<<"Rectangles::Update: COLLISION\n";
			//		m_deltaX = 0;
			//		m_deltaY = 0;
			//	}
			//	// if colission 
			//	m_x = m_x + m_deltaX / m_k;
			//	m_y = m_y + m_deltaY / m_k;
			//}
		}
}