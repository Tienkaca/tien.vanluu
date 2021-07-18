#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
	m_e = EPSILON;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_c[i][j] = 0;
		}
	}
}

CollisionManager::~CollisionManager()
{

}
bool check(vector<float> r1, vector<float> r2)
{
	/*cout << "r1:"<<r1[0]<<"\t"<<r1[1]<<"\t"<<r1[2]<<"\t"<<r1[3]<<"\n";
	cout << "r2:" << r2[0] << "\t" << r2[1] << "\t" << r2[2] << "\t" << r2[3] << "\n";*/
	bool sts = false;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			float x = r1[i*2];
			float y = r1[j*2 + 1];
			
			if (r2[0] <= x && x <= r2[2] && r2[1] <= y && y <= r2[3])
				sts =  true;
		}
	}
	return sts;
}
void CollisionManager::checkm_c(int j, int size)
{
	int i = 0;
	while (i < size)
	{
		if (!(i == j))
		{
			if (m_c[i][j] == 1)
			{
				if (m_c[size - 1][i] == 0)
				{
					m_c[size - 1][i] = 1;
					m_c[i][size - 1] = 1;
					checkm_c(i,size);
				}
			}
		}
		i++;
	}
	
}
void CollisionManager::showm_c(int n)
{
	cout << "M_C:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << m_c[i][j] << "\t";
		}
		cout << "\n";
	}
}
void CollisionManager::updatem_c(std::vector<Object*> Objects)
{
	int size = Objects.size();
	for (int i = 0; i < Objects.size(); i++)
	{
		for (int j = 0; j < Objects.size(); j++)
		{
			if (i < j)
			{
				static bool stsCollisF = 1;
				if (checkCollision(Objects[i], Objects[j]))
				{

					m_c[i][j] = 1;
					m_c[j][i] = 1;
					/*if (stsCollisF)
					{
						setVelCollision(Objects[i], Objects[j]);
						stsCollisF = 0;
					}
					if(j == size -1)
					{
						Objects[i]->setPlaneCollis();
					}*/
				}
				else
				{
					stsCollisF = 1;
					m_c[i][j] = 0;
					m_c[j][i] = 0;
					/*if (j == size - 1)
					{
						Objects[i]->resetPlaneCollis();
					}*/
				}
			}
		}
	}
	for (int i = 0; i < size; i++)
	{
		m_c[size - 1][i] = 0;
	}
}
void CollisionManager::setObjectCollis(std::vector<Object*> Objects)
{

	int n = Objects.size();
	int min = 10;
	int active;
	for (int i = 0; i < n; i++)
	{
		if (m_c[n-1][i])
		{
			Objects[i]->setCollis();
			Objects[i]->setPlaneCollis();
		}
		else
		{
			Objects[i]->resetPlaneCollis();
			int m = 0;
			for (int j = 0; j < n; j++)
			{
				if (!(i == j))
					m += m_c[j][i];
			}
			if (m > 0)
			{
				Objects[i]->setCollis();
			}
			else if (m == 0)
			{

				Objects[i]->resetCollis();
			}
			else
			{
			}
			if (min > m && m>0)
			{
				min = m;
				active = i;
			}
			
		}
	}
	/*if (active < n)
	{
		for (int i = 0; i < n; i++)
		{
			m_c[i][active] = 0;
			
		}
		Objects[active]->resetCollis();

	}*/
	showm_c(n);
	
}
void CollisionManager::updateCollision(std::vector<Object*> Objects)
{
	int size = Objects.size();
	updatem_c(Objects);

	checkm_c(size - 1, size);
	setObjectCollis(Objects);
	static bool sts = 1;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i < j)
			{
				if (sts && Objects[i]->isCollis() && Objects[j]->isCollis())
				{
					setVelCollision(Objects[i], Objects[j]);
					sts = 0;
				}
				else
				{
					sts = 1;
				}
			}
		}
	}

}
bool CollisionManager::checkCollision(Object* O1, Object* O2)
{
	vector<float> temp = O2->getData();
	bool sts = false;
	if (O1->shape() == 4 && O2->shape() == 4)
	{
		if (checkRectRectCollision(O1, O2))
		{
			sts = true;
			//cout << "RECT RECT COLLIS\n";
		}
	}
	else if (O1->shape() == 3 && O2->shape() == 3)
	{
		if (checkCirCirCollision(O1, O2))
		{
			sts = true;
			//cout << "CIR CIR COLLIS\n";
		}
	}
	else if (O1->shape() == 4 && O2->shape() == 3)
	{
		if (checkRectCirCollision(O1, O2))
		{
			sts = true;
			//cout << "RECT CIR COLLIS\n";
		}
	}
	else if (O1->shape() == 3 && O2->shape() == 4)
	{
		if (checkRectCirCollision(O2, O1))
		{
			sts = true;
			//cout << "RECT CIR COLLIS\n";
		}
	}
	else if (O1->shape() == 3 && O2->shape() == 5)
	{
		if (checkCirPlaneCollision(O1,O2))
		{
			sts = true;
			//cout << "PLANE CIR COLLIS\n";
		}
	}
	else if (O1->shape() == 4 && O2->shape() == 5)

	{
		if (checkRectPlaneCollision(O1,O2))
		{
			sts = true;
			//cout << "PLANE RECT COLLIS\n";
		}
	}
	return sts;
}

bool CollisionManager::checkRectRectCollision(Object* R1, Object* R2)
{
	vector<float> d1 = R1->getData();
	vector<float> d2 = R2->getData();
	bool sts = false;
	
	if (check(d1, d2) || check(d2, d1))
	{
		
		if (abs(d1[0] - d2[2]) < m_e)
		{
			R1->setCollisArg(8);
			R2->setCollisArg(4);
			sts = true;
		}
		else if (abs(d1[2] - d2[0]) < m_e)
		{
			R1->setCollisArg(4);
			R2->setCollisArg(8);
			sts = true;
		}
		else if (abs(d1[1] - d2[3]) < m_e)
		{
			R1->setCollisArg(2);
			R2->setCollisArg(6);
			sts = true;
		}
		else if (abs(d1[3] - d2[1]) < m_e)
		{
			R1->setCollisArg(6);
			R2->setCollisArg(2);
			sts = true;
		}
		sts = true;
		
	}
	return sts;
}
bool CollisionManager::checkCirCirCollision(Object* C1, Object* C2)
{
	vector<float> d1 = C1->getData();
	vector<float> d2 = C2->getData();
	bool sts = false;
	float dx = d1[0] - d2[0];
	float dy = d1[1] - d2[1];
	float R = d1[2] + d2[2];
	
	if (sqrt(dx*dx + dy*dy )<= R)
		sts = true;
	return sts;
}


bool CollisionManager::checkRectPlaneCollision(Object* R, Object* P)
{
	vector<float> d1 = R->getData();
	vector<float> d2 = P->getData();
	bool sts = false;
	if (d1[0] - d2[0] < m_e)
	{
		//cout << "VAO LUON0\n";
		R->setCollisArg(8);
		sts = true;
	}
	else if (abs(d1[1] - d2[1])< m_e)
	{
		//cout << "VAO LUON1\n";
		R->setCollisArg(2);
		sts = true;
	}
	else if (abs(d2[2] - d1[2]) < m_e)
	{
		//cout << "VAO LUON2\n";
		R->setCollisArg(4);
		sts = true;
	}
	else if (abs(d2[3] - d1[3]) < m_e)
	{
		//cout << "VAO LUON3\n";
		R->setCollisArg(6);
		sts = true;
	}
	
	return sts;
}
bool CollisionManager::checkCirPlaneCollision(Object* C, Object* P)
{
	vector<float> d1 = C->getData();
	vector<float> d2 = P->getData();
	float R = d1[2];
	bool sts = false;
	if (abs(d1[0] - d2[0]) < R)
	{
		C->setCollisArg(PI);
		sts = true;
	}
	else if (abs(d1[0] - d2[2]) < R)
	{
		C->setCollisArg(0);
		sts = true;
	}
	else if (abs(d1[1] - d2[1]) < R)
	{
		C->setCollisArg(PI/2);
		sts = true;
	}
	else if (abs(d1[1] - d2[3]) < R)
	{
		C->setCollisArg(-PI/2);
		sts = true;
	}
	return sts;
}
bool CollisionManager::checkRectCirCollision(Object* R, Object* C)
{
	vector<float> d1 = R->getData();
	vector<float> d2 = C->getData();
	float x1 = d1[0];
	float y1 = d1[1];
	float x2 = d1[2];
	float y2 = d1[3];
	float xc = d2[0];
	float yc = d2[1];
	float r = d2[2] + EPSILON;
	float x, y;
	bool sts = false;
	
	float cheo = sqrt((d1[2] - d1[0])*(d1[2] - d1[0]) + (d1[3] - d1[1])*(d1[3] - d1[1])) / 2;
	if (!(x1 <= xc && xc <= x2 || y1 <= yc && yc <= y2))
	{
		//cout << "CollisionManager::checkRectCirCollision\n";
		if (dis(xc, yc, (x1 + x2) / 2, (y1 + y2) / 2) < (r + cheo))
			sts = true;
	}
	else
	{
		if (x1 <= xc && xc <= x2)
		{
			//cout << "CollisionManager::checkRectCirCollision Y :\n" << r << "\t" << abs(y2 - yc) << "\t" << abs(y1 - yc) << "\n";
			if (abs(y2 - yc)< r || abs((y1 - yc))< r)
			{
				//cout << "CollisionManager::checkRectCirCollision Y :\n" << r << "\t" << abs(y2 - yc) << "\t" << abs(y1 - yc) << "\n";
				sts = true;
			}
		}
		if (y1 <= yc && yc <= y2)
		{
			if (abs(x1 - xc) < r || abs(x2 - xc) < r)
			{
				//cout << "CollisionManager::checkRectCirCollision X :\n" << r << "\t" << abs(x1 - xc) << "\t" << abs(x2 - xc) << "\n";
				sts = true;
			}
		}
	}
	
	return sts;
}
void CollisionManager::setVelCollision(Object* O1, Object* O2)
{
	float m1 = O1->getMass();
	float m2 = O2->getMass();
	vector<float> v1 = O1->getDeltaS();
	vector<float> v2 = O2->getDeltaS();
	float v1x = ((m1 - m2)*v1[0] + 2*m2*v2[0])/(m1 + m2);
	float v1y = ((m1 - m2)*v1[1] + 2 * m2*v2[1]) / (m1 + m2);
	float v2x = ((m2 - m1)*v2[0] + 2 * m1*v1[0]) / (m1 + m2);
	float v2y = ((m2 - m1)*v2[1] + 2 * m1*v1[1]) / (m1 + m2);
	if (O1->IsFalling() && O1->isPlaneCollis() && O1->isCollis())
		O1->setDeltaS(0, 0);
	else
		O1->setDeltaS(v1x, v1y);
	if (O2->IsFalling() && O2->isPlaneCollis() && O2->isCollis())
		O2->setDeltaS(0, 0);
	else
		O2->setDeltaS(v2x, v2y);
}