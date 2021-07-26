#include "stdafx.h"
#include "TerrainObject.h"


TerrainObject::TerrainObject()
{
}


TerrainObject::~TerrainObject()
{
}

int TerrainObject::Init(Vector3 _pos, Vector3 _rot, Vector3 _scale, Shaders* _shader, std::vector<Texture*> _texts, int* textArray, int textCount, Models* _model)
{
	
	m_pos = _pos;
	m_rot = _rot*PI / 180;
	m_scale = _scale;
	m_model = _model;
	for (int i = 0; i < textCount; i++)
	{
		int iTextUnit;
		m_texts.push_back(_texts.at(textArray[i]));
		m_texts.at(i)->Init();
	}
	m_shaders = _shader;
	m_shaders->Init();
	InitHeightMap();
	m_textsLoc[0] = glGetUniformLocation(m_shaders->program, "u_texture0");
	m_textsLoc[1] = glGetUniformLocation(m_shaders->program, "u_texture1");
	m_textsLoc[2] = glGetUniformLocation(m_shaders->program, "u_texture2");
	m_textsLoc[3] = glGetUniformLocation(m_shaders->program, "u_texture3");

	
	 return 0;
}
void TerrainObject::InitHeightMap()
{
	Vertex *Vertices;
	int *Indices;
	int w, h, bpp;
	m_model->LoadModel(Vertices, Indices);
	char* Height = LoadTGA(m_texts.at(m_texts.size() - 1)->m_file, &w, &h, &bpp);
	for (int i = 0; i < m_model->m_nrVertices; i++)
	{
		int u = (int)(Vertices[i].uv.x*w);
		int v = (int)(Vertices[i].uv.y*h);
		float hight = (float)(Height[(u*w + v) * 3]);
		if (hight >= 0)
		{
			hight = hight * 10 / 256;
		}
		else
		{
			hight = (hight + 256) * 10 / 256;
		}
		Vertices[i].pos.y = hight;
	}
	m_model->Init(Vertices, Indices);
	delete[] Height;
}
void TerrainObject::Draw()
{
	glUseProgram(m_shaders->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_model->m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->m_iboId);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texts.at(0)->m_textId);
	glUniform1i(m_textsLoc[0], 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texts.at(1)->m_textId);
	glUniform1i(m_textsLoc[1], 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_texts.at(2)->m_textId);
	glUniform1i(m_textsLoc[2], 2);
		
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_texts.at(3)->m_textId);
	glUniform1i(m_textsLoc[3], 3);
		
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, m_texts.at(4)->m_textId);
	glUniform1i(m_textsLoc[4], 4);
		

	if (m_shaders->positionAttribute != -1 && m_shaders->uvAttribute != -1)
	{
		glEnableVertexAttribArray(m_shaders->positionAttribute);
		glEnableVertexAttribArray(m_shaders->uvAttribute);
		glVertexAttribPointer(m_shaders->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(m_shaders->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3) * 4);
		Matrix W = GetWorldMatrix(true);
		Matrix VP = CameraLookAt::GetInstance()->GetViewPerspectiveMatrix();
		Matrix WVP = W*VP;
		glUniformMatrix4fv(m_shaders->uniWVP, 1, GL_FALSE, (const GLfloat*)WVP.m);
	}
	glDrawElements(GL_TRIANGLES, m_model->m_nrIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}