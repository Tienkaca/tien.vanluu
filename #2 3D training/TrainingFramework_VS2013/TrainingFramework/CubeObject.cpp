#include "stdafx.h"
#include "CubeObject.h"


CubeObject::CubeObject()
{
}


CubeObject::~CubeObject()
{
}
int CubeObject::Init(Vector3 _pos, Vector3 _rot, Vector3 _scale, Shaders* _shader, std::vector<Texture*> _texts, int* textArray, int textCount, Models* _model)
{
	m_pos = _pos;
	m_rot = _rot*PI / 180;
	m_scale = _scale;
	m_model = _model;
	m_model->Init();
	m_textCube = _texts.at(textArray[0]);
	m_textCube->InitCube();
	m_shaders = _shader;
	m_shaders->Init();
	m_uniCubeTextLoc = glGetUniformLocation(m_shaders->program, "u_samplerCubeMap");
	return 0;
}
void CubeObject::Draw()
{
	glUseProgram(m_shaders->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_model->m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->m_iboId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textCube->m_textId);
	glUniform1i(m_uniCubeTextLoc, 0);
	if (m_shaders->positionAttribute != -1)
	{
		glEnableVertexAttribArray(m_shaders->positionAttribute);
		glVertexAttribPointer(m_shaders->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		Matrix W = GetWorldMatrix(true);
		Matrix VP = CameraLookAt::GetInstance()->GetViewPerspectiveMatrix();
		Matrix WVP = W*VP;
		glUniformMatrix4fv(m_shaders->uniWVP, 1, GL_FALSE, (const GLfloat*)WVP.m);
	}
	glDrawElements(GL_TRIANGLES, m_model->m_nrIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}