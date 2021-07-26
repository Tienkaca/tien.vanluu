#include "stdafx.h"
#include "FireObject.h"


FireObject::FireObject()
{
}


FireObject::~FireObject()
{
}
int FireObject::Init(Vector3 _pos, Vector3 _rot, Vector3 _scale, Shaders* _shader, std::vector<Texture*> _texts, int* textArray, int textCount, Models* _model)
{
	m_pos = _pos;
	m_rot = _rot*PI / 180;
	m_scale = _scale;
	m_model = _model;
	m_model->Init();
	for (int i = 0; i < textCount; i++)
	{
		m_texts.push_back(_texts.at(textArray[i]));
		m_texts.at(i)->Init();
	}
	m_shaders = _shader;
	m_shaders->Init();
	glUseProgram(m_shaders->program);
	m_uniDisplacementMapText = glGetUniformLocation(m_shaders->program, "u_Displacement");
	m_uniFireText = glGetUniformLocation(m_shaders->program, "u_fireText");
	m_uniMaskText = glGetUniformLocation(m_shaders->program, "u_maskText");
	
	return 0;
}
void FireObject::Draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glUseProgram(m_shaders->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_model->m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->m_iboId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texts.at(0)->m_textId);
	glUniform1i(m_uniDisplacementMapText, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texts.at(1)->m_textId);
	glUniform1i(m_uniFireText,1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_texts.at(2)->m_textId);
	glUniform1i(m_uniMaskText, 2);
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
		glUniform1f(m_shaders->uniUtime, CameraLookAt::GetInstance()->mp_utime);
	}
	glDrawElements(GL_TRIANGLES, m_model->m_nrIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
}
