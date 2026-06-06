#define GLFW_INCLUDE_NONE
#include<iostream>
#include<GLFW/glfw3.h>
#include<glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void resizeFallBack(GLFWwindow* window, int width, int height);
void shaderErrorHandling(const unsigned int& shader);
void ProgramError(unsigned int& program);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(800,600,"Texture",NULL,NULL);
	glfwMakeContextCurrent(window);
	if (!window)
	{
		std::cout << "ERROR ESTABLISHING THE WINDOW" << std::endl;
	}
	float vertex[] = {
	-0.5f,-0.5f,0.0f,	1.0f,0.0f,0.0f,1.0f,  0.0f,0.0f,
	 0.5f,-0.5f,0.0f,	0.0f,1.0f,0.0f,1.0f,  1.0f,0.0f,
	 0.0f,0.0f,0.0f,	0.0f,0.0f,1.0f,1.0f,  0.0f,1.0f
	};

	unsigned int VAO, VBO;
	int width, height, nrChannels;
	unsigned char* data=stbi_load("img/wall.jpg",&width,&height,&nrChannels,0);
	unsigned int texture;
	if (!data)
	{
		std::cout << "Error" << std::endl;
	}
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR ESTABLISHING THE GLAD" << std::endl;
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window,resizeFallBack);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW);


	const char *vertexShader = R"(
	#version 330 core

	layout(location = 0) in vec3 aPosx;
	layout(location = 1) in vec4 aColor;
	layout(location = 2) in vec2 aTextCoord;

	out vec4 ourColor;
	out vec2 textureCoord;
	void main()
	{
		gl_Position=vec4(aPosx,1.0f);
		ourColor=aColor;
		textureCoord=aTextCoord;		
	}
	)";
	const char *fragmentShader = R"(
	#version 330 core
	in vec4 ourColor;
	in vec2 textureCoord;

	out vec4 Fragcolor;
	
	uniform sampler2D ourTexture;
	void main ()
	{
	Fragcolor=texture(ourTexture,textureCoord)*ourColor;
	}
	)";
	unsigned int VSA, FSA;//addresses;
	VSA = glCreateShader(GL_VERTEX_SHADER);
	FSA = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(VSA, 1, &vertexShader, NULL);
	glShaderSource(FSA, 1, &fragmentShader, NULL);
	glCompileShader(VSA);
	glCompileShader(FSA);
	shaderErrorHandling(FSA);
	shaderErrorHandling(VSA);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,VSA);
	glAttachShader(shaderProgram,FSA);
	glLinkProgram(shaderProgram);
	ProgramError(shaderProgram);

	glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4 , GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,9*sizeof(float),(void*)(7*sizeof(float)));
	glEnableVertexAttribArray(2);

	glUseProgram(shaderProgram);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.3f,0.3f,1.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
void resizeFallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void shaderErrorHandling(const unsigned int& shader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout<< "Shader Error" <<infoLog<< std::endl;
	}
}
void ProgramError(unsigned int& program)
{
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Linking Error Error" << infoLog << std::endl;
	}
}