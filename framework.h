#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include<iostream>
#include <sstream>
#include<gl\glew.h>
#include<GL\GLU.h>
#include<gl\freeglut.h>

namespace Framework
{
  GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename)
	{
		GLuint shader = glCreateShader(eShaderType);
		//std::string strFilename = FindFileOrThrow(strShaderFilename);
		//std::ifstream shaderFile(strFilename.c_str());
		std::ifstream shaderFile(strShaderFilename.c_str());
		std::stringstream shaderData;

		shaderData << shaderFile.rdbuf();
		std::string s= shaderData.str();
		const char *strFileData = s.c_str();

		glShaderSource(shader, 1, &strFileData, NULL);
		shaderFile.close();

		//std::cout<<;

		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

			const char *strShaderType = NULL;
			switch(eShaderType)
			{
			case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
			case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
			case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
			}

			fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
			delete[] strInfoLog;
		}

	return shader;
	}

	GLuint CreateProgram(const std::vector<GLuint> &shaderList)
	{
		GLuint program = glCreateProgram();

		for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
			glAttachShader(program, shaderList[iLoop]);

		glLinkProgram(program);

		GLint status;
		glGetProgramiv (program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
			fprintf(stderr, "Linker failure: %s\n", strInfoLog);
			delete[] strInfoLog;
		}

		for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
			glDetachShader(program, shaderList[iLoop]);

		std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
		return program;
	}
}
