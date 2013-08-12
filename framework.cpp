#include<iostream>
#include<gl\glew.h>
#include<GL\GLU.h>
#include<gl\freeglut.h>
#include <algorithm>
#include <string>
#include <vector>
#include <stdio.h>
#include "framework.h"


GLuint theProgram, positionBufferObject,vao;

void InitializeProgram()
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER,"VS1.txt"));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER,"FS2.txt"));

	theProgram = Framework::CreateProgram(shaderList);
}

const float vertexPositions[] = 
{
	0.75f, 0.75f, 0.0f, 1.0f,
	0.75f, -0.75f, 0.0f, 1.0f,
	-0.75f, -0.75f, 0.0f, 1.0f,
};




void InitializeVertexBuffer()
{
	glGenBuffers(1, &positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(theProgram);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glUseProgram(0);

	glutSwapBuffers();
}

void init()
{
	glewInit();
	InitializeProgram();
	InitializeVertexBuffer();
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

int main(int agrc,char **agrv)
{
	glutInit(&agrc,agrv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //for animation programs GLUT_DOUBLE , GLUT_DEPTH for 3d apps
	glutInitWindowSize(500,500);			//screen resolution (width,height)
	glutCreateWindow("shader");
	glutInitWindowPosition(50,25);
	glutDisplayFunc(display);		//display function
	init();							//put all initialization commands in this funtion
	glutMainLoop();

	return 0;
}