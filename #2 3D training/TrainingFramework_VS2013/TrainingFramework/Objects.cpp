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
	m_pos = _pos;
	m_rot = _rot*PI / 180;
	m_scale = _scale;
	m_model = _model;
	m_model->Init();
	m_text = _text;
	m_text->Init(0);
	m_shaders = _shader;
	return m_shaders->Init();
}
int Objects::Init(Vector3 _pos, Vector3 _rot, Vector3 _scale, Shaders* _shader, std::vector<Texture*> _texts,int* _textId,int nbTexts, Models* _model)
{
	
	m_pos = _pos;
	m_rot = _rot*PI / 180;
	m_scale = _scale;
	m_model = _model;
	m_model->Init();
	for (int i = 0; i < nbTexts; i++)
	{
		m_texts.push_back(_texts.at(_textId[i]));
		m_texts.at(i)->Init(2*i);
		mp_isCube = m_texts.at(i)->mp_isCubeTexture;
	}
	m_shaders = _shader;
	if (nbTexts > 1)
	{
		int textLoc[4];
		textLoc[0] = glGetUniformLocation(m_shaders->program, "u_texture0");
		glUniform1i(textLoc[0], 0);
		textLoc[1] = glGetUniformLocation(m_shaders->program, "u_texture1");
		glUniform1i(textLoc[1], 2);
		textLoc[2] = glGetUniformLocation(m_shaders->program, "u_texture2");
		glUniform1i(textLoc[2], 4);
		textLoc[3] = glGetUniformLocation(m_shaders->program, "u_texture3");
		glUniform1i(textLoc[3], 6);
		m_shaders->isMultiText = 1;
	}
	else
	{
		int loc;
		loc = glGetUniformLocation(m_shaders->program, "u_texture");
		glUniform1i(loc, 0);
		m_shaders->isMultiText = 0;
	}
		
	
	
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
	if (m_shaders->isMultiText)
	{
		for (int i = 0; i < m_texts.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + 2 * i);
			int m = m_texts.at(0)->m_textId;
			glBindTexture(GL_TEXTURE_2D, m_texts.at(i)->m_textId);
		}
	}
	else
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, m_texts.at(0)->m_textId);
	}
	if (m_shaders->positionAttribute != -1 && m_shaders->uvAttribute != -1)
	{
		glEnableVertexAttribArray(m_shaders->positionAttribute);
		//glEnableVertexAttribArray(myShaders.colorAttribute);z
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
void Objects::DrawCube()
{
	glUseProgram(m_shaders->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_model->m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->m_iboId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_text->m_textId);
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