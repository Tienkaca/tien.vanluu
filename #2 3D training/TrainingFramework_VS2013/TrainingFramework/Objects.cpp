#include "stdafx.h"
#include "Objects.h"


Objects::Objects()
{
	mp_isCube = 0;
	mp_isMutiText = 0;
}


Objects::~Objects()
{
}
int Objects::Init(Vector3 _pos, Vector3 _rot, Vector3 _scale, Shaders* _shader, Texture* _text, Models* _model)
{
	mp_isCube = 1;
	m_pos = _pos;
	m_rot = _rot*PI / 180;
	m_scale = _scale;
	m_model = _model;
	m_model->Init();
	m_textCube = _text;
	m_textCube->Init(0);
	m_shaders = _shader;
	return m_shaders->Init(false);
}
int Objects::Init(Vector3 _pos, Vector3 _rot, Vector3 _scale, Shaders* _shader, std::vector<Texture*> _texts,int* textArray, int textCount , Models* _model)
{
	mp_isCube = 0;
	if (textCount > 1)
		mp_isMutiText = 1;
	m_pos = _pos;
	m_rot = _rot*PI / 180;
	m_scale = _scale;
	m_model = _model;
	m_model->Init();
	for (int i = 0; i < textCount; i++)
	{
		int iTextUnit;
		m_texts.push_back(_texts.at(textArray[i]));
		if (textCount > 1)
		{
			iTextUnit = i + 1;
		}
		else
		{
			iTextUnit = i;
		}
		m_texts.at(i)->Init(iTextUnit);
	}
	m_shaders = _shader;
	return m_shaders->Init(mp_isMutiText);
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
void Objects::Draw(ESContext *esContext)
{
	if (mp_isCube)
		DrawCube();
	else
		DrawObj();
}
void Objects::DrawObj()
{
	glUseProgram(m_shaders->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_model->m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->m_iboId);
	if (mp_isMutiText)
	{
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texts.at(0)->m_textId);
	glUniform1i(m_shaders->uLoc[0], 1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D , m_texts.at(1)->m_textId);
	glUniform1i(m_shaders->uLoc[1], 2);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_texts.at(2)->m_textId);
	glUniform1i(m_shaders->uLoc[2], 3);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, m_texts.at(3)->m_textId);
	glUniform1i(m_shaders->uLoc[3], 4);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, m_texts.at(4)->m_textId);
	glUniform1i(m_shaders->uLoc[4], 5);
	}
	else
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, m_texts.at(0)->m_textId);
		
	}
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
	//glBindTexture(GL_TEXTURE_2D, 0);
}
void Objects::DrawCube()
{
	glUseProgram(m_shaders->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_model->m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->m_iboId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textCube->m_textId);
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