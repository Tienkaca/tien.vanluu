#include <stdafx.h>
#include "Shaders.h"
Shaders::Shaders()
{
	for (int i = 0; i < 10; i++)
		state[i] = 0;
}
int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	colorAttribute = glGetAttribLocation(program, "a_color");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	int iTextureLoc = glGetUniformLocation(program,"u_texture");
	glUniform1i(iTextureLoc, 0);
	uniWVP = glGetUniformLocation(program, "u_WVP");
	glUniformMatrix4fv(uniWVP, 1, GL_FALSE, 0);
	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}