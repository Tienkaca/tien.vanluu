#include "stdafx.h"
#include "Models.h"


Models::Models()
{

}


Models::~Models()
{
}
void Models::LoadModel(Vertex* &verticeData, int* &indiceData)
{
	FILE *file;
	file = fopen(m_file, "r");
	if (!file)
		std::cout << "Can not open this file" << std::endl;
	else
		std::cout << "File is opened" << std::endl;

	fscanf(file, "NrVertices: %d\n", &m_nrVertices);
	verticeData = new Vertex[m_nrVertices];
	int line;
	for (int i = 0; i < m_nrVertices; i++)
	{
		fscanf(file, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n", &line,
			&verticeData[i].pos.x, &verticeData[i].pos.y, &verticeData[i].pos.z,
			&verticeData[i].normal.x, &verticeData[i].normal.y, &verticeData[i].normal.z,
			&verticeData[i].binormal.x, &verticeData[i].binormal.y, &verticeData[i].binormal.z,
			&verticeData[i].tagent.x, &verticeData[i].tagent.y, &verticeData[i].tagent.z,
			&verticeData[i].uv.x, &verticeData[i].uv.y);
		// CHU Y CHU Y
		verticeData[i].pos.y = verticeData[i].pos.y - 1.0f;
	}

	fscanf(file, "NrIndices: %d\n", &m_nrIndices);
	indiceData = new int[m_nrIndices];
	for (int i = 0; i < m_nrIndices / 3; i++)
	{
		fscanf(file, "   %d.    %d,    %d,    %d\n", &line, &indiceData[3 * i], &indiceData[3 * i + 1], &indiceData[3 * i + 2]);
		//std::cout<<"IN:" << indiceData[3 * i] << "\t" << indiceData[3 * i + 1] << "\t" << &indiceData[3 * i + 2] << "\n";
	}
	/*std::cout << "Models::LoadModel:\n";
	std::cout << m_file << "\n";
	for (int i = 0; i < m_nrIndices / 3; i++)
	{
		std::cout <<"OUT"<< indiceData[3 * i] << "\t" << indiceData[3 * i + 1] << "\t" << indiceData[3 * i + 2] << "\n";
	}*/

	fclose(file);
}
void Models::Init()
{
	Vertex *verticesData;
	int *indiceData;
	LoadModel(verticesData, indiceData);
	if (verticesData && indiceData)
	{
		glGenBuffers(1, &m_vboId);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*m_nrVertices, verticesData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &m_iboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_nrIndices, indiceData, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	delete[] verticesData;
	delete[] indiceData;
}