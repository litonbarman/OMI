#ifndef __SHADER_HELPER__
#define __SHADER_HELPER__

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <GL/glew.h>

GLuint LoadShader(const char* vertex_file_path, const char* fragment_file_path) {
	GLuint VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path);
	
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s, you are not in the right directory\n", vertex_file_path);
		system("pause");
		return 0;
	}

	std::string FragmentShaderCode;
	std::ifstream FragementShaderStream(fragment_file_path);

	if (FragementShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragementShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragementShaderStream.close();
	}
	else {
		printf("Impossible to open %s, you are not in the right directory\n", fragment_file_path);
		return 0;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	printf("Compiling Vertex Shader\n");
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderId, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderId);

	glGetShaderiv(VertexShaderId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderId, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}
	else {
		printf("Done\n");
	}
	
	printf("Compiling Fragment Shader\n");
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderId, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderId);

	glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(FragmentShaderId, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}
	else {
		printf("Done\n");
	}

	// Linking the shaders
	printf("Linking the shader programs\n");
	GLuint ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);

	// now checking the linked program
	glGetProgramiv(ProgramId, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramId, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	else {
		printf("Done\n");
	}

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	return ProgramId;
}


#endif