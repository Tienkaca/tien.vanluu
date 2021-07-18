#include "stdafx.h"
#include "Object.h"


Object::Object(Vector3 _scale, Vector4 _pos, Vector4 _rot, char* _nfgId, char* _tgaId, char* _VSShaderId, char* _FTShaderId )
{
	m_vboId = 0;
	m_iboId = 0;
	m_textureId = 0;
	m_nrVertices = 0;
	m_nrIndices = 0;
	m_nfgId = _nfgId;
	m_tdaId = _tgaId;
	m_VSShaderId= _VSShaderId;
	m_FTShaderId= _FTShaderId;
	m_pos = _pos;
	m_rot = _rot;
	m_scale = _scale;
}


Object::~Object()
{
	glDeleteBuffers(1, &m_vboId);
	glDeleteBuffers(1, &m_iboId);
	glDeleteBuffers(1, &m_textureId);
}
Matrix Object::GetWorldMatrix(bool _forward)
{
	Matrix Rx, Ry, Rz, R;
	Matrix T;
	Matrix S;
	Matrix W;
	if (_forward)
	{
		Rx.SetRotationX(m_rot.x);
		Ry.SetRotationY(m_rot.y);
		Rz.SetRotationZ(m_rot.z);
		R = Rz*Rx*Ry;
		T.SetTranslation(m_pos.x, m_pos.y, m_pos.z);
		S.SetScale(m_scale.x, m_scale.y, m_scale.z);
		W = S*R*T;
	}
	else
	{
		Rx.SetRotationX(-m_rot.x);
		Ry.SetRotationY(-m_rot.y);
		Rz.SetRotationZ(-m_rot.z);
		R = Ry*Rx*Rz;
		T.SetTranslation(-m_pos.x, -m_pos.y, -m_pos.z);
		S.SetScale(1/m_scale.x, 1/m_scale.y, 1/m_scale.z);
		W = T*R*S;
	}
	return W;
}
void Object::InitData(Vertex* &verticeData, int* &indiceData)
{
	
	FILE *file;
	file = fopen(m_nfgId, "r");
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
	}
	fclose(file);
}
int Object::Init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex *verticesData;
	int *indiceData;
	
	InitData(verticesData, indiceData);
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

		//TEXTure
		int w, h, bpp;
		glGenTextures(1, &m_textureId);
		glBindTexture(GL_TEXTURE_2D, m_textureId);
		char *imageData = LoadTGA(m_tdaId, &w, &h, &bpp);

		if (bpp == 24)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		}
		delete[] imageData;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glGenerateMipmap(GL_TEXTURE_2D);

		delete[] verticesData;
		delete[] indiceData;
	}
	//creation of shaders and program 
	return m_shaders.Init(m_VSShaderId, m_FTShaderId);
	
}

void Object::Draw(ESContext *esContext)
{
	//glEnable(GL_DEPTH_TEST);
	//glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(m_shaders.program);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);

	if (m_shaders.positionAttribute != -1 && m_shaders.uvAttribute != -1)
	{
		glEnableVertexAttribArray(m_shaders.positionAttribute);
		//glEnableVertexAttribArray(myShaders.colorAttribute);
		glEnableVertexAttribArray(m_shaders.uvAttribute);
		glVertexAttribPointer(m_shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		//glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3));
		glVertexAttribPointer(m_shaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3) * 4);
		Matrix W = GetWorldMatrix(true);
		Matrix VP = CameraLookAt::GetInstance()->GetViewPerspectiveMatrix();
		Matrix WVP = W*VP;
		glUniformMatrix4fv(m_shaders.uniWVP, 1, GL_FALSE, (const GLfloat*)WVP.m);
	}

	glDrawElements(GL_TRIANGLES, m_nrIndices, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
	
}