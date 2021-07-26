#pragma once
#include "../Utilities/utilities.h"

class Shaders
{
public:
	int id;
	bool state[10];
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint colorAttribute;
	GLint uvAttribute;
	GLint uniWVP;
	int uLoc[10];
	int Init(char * fileVertexShader, char * fileFragmentShader);
	int Init(bool sts);
	Shaders();
	~Shaders();
};