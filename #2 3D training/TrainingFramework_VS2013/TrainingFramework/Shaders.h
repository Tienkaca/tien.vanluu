#pragma once
#include "../Utilities/utilities.h"

class Shaders
{
public:
	int id;
	int isMultiText;
	char fileVS[260];
	char fileFS[260];
	int textLoc[10];
	bool state[10];
	GLuint program, vertexShader, fragmentShader;
	
	GLint positionAttribute;
	GLint colorAttribute;
	GLint uvAttribute;
	GLint uniWVP;
	int Init(char * fileVertexShader, char * fileFragmentShader);
	int Init();
	Shaders();
	~Shaders();
};