#include "stdafx.h"
#include "Objects.h"


Objects::Objects()
{
}


Objects::~Objects()
{
}
int Objects::Init(Vector3 _pos, Vector3 _rot, Vector3 _scale, Shaders* _shader, Texture* _text, Models* _model)
{
	mp_isCube = _text->mp_isCubeTexture;
	m_pos = _pos;
	m_rot = _rot*PI / 180;
	m_scale = _scale;
	m_model = _model;
	m_model->Init();
	m_text = _text;
	m_text->Init();
	m_shaders = _shader;
	return m_shaders->Init();
}
Matrix Objects::GetWorldMatrix(bool _forward)
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
		S.SetScale(1 / m_scale.x, 1 / m_scale.y, 1 / m_scale.z);
		W = T*R*S;
	}
	return W;
}
void Objects::DrawObj(ESContext *esContext)
{
	
	glUseProgram(m_shaders->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_model->m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_model->m_iboId);
	glBindTexture(GL_TEXTURE_2D,m_text->m_textId);
	if (m_shaders->positionAttribute != -1 && m_shaders->uvAttribute != -1)
	{
		glEnableVertexAttribArray(m_shaders->positionAttribute);
		//glEnableVertexAttribArray(myShaders.colorAttribute);
		glEnableVertexAttribArray(m_shaders->uvAttribute);
		glVertexAttribPointer(m_shaders->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		//glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3));
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
void Objects::DrawCube(ESContext *esContext)
{
	glDisable(GL_DEPTH_TEST);
	glUseProgram(m_shaders->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_model->m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->m_iboId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_text->m_textId);
	if (m_shaders->positionAttribute)
	{
		glEnableVertexAttribArray(m_shaders->positionAttribute);
		glVertexAttribPointer(m_shaders->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		
		Matrix W = GetWorldMatrix(true);
		Matrix VP = CameraLookAt::GetInstance()->GetViewPerspectiveMatrix();
		Matrix WVP = W*VP;
		glUniformMatrix4fv(m_shaders->uniWVP, 1, GL_FALSE, (const GLfloat*)WVP.m);
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_model->m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->m_iboId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_text->m_textId);
	glEnable(GL_DEPTH_TEST);
}
void Objects::Draw(ESContext *esContext)
{
	if (mp_isCube)
		DrawCube(esContext);
	else
		DrawObj(esContext);
}