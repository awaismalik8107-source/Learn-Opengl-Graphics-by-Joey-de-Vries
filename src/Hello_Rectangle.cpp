#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<iostream>

void setResizeFallBack(GLFWwindow* window, int width, int height);
void inputBuffer(GLFWwindow* window);

int main()
{
	//--------------Setting Up the Windows hints---------------//
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//---------------Setting Up Variables------------//
	float vertex[] = {
	0.5f,0.5f,0.0f,//0
	0.5f,-1.0f,0.0f,//1
	-0.5f,-0.5f,0.0f,//2
	-0.5f,0.5f,0.0f//3
	};
	unsigned int indices [] = {
		0,1,3,//t1
		1,2,3
	};
	unsigned int VAO,VBO,EBO;
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Rectangle", NULL, NULL);
	if (!window)
	{
		std::cout << "ERROR MAKING THE WINDOW" << std::endl;
		glfwTerminate();
		return 0;
	}
	glfwMakeContextCurrent(window);
	//------------------Loading GLad------------------//
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR IN STARTING THE GLAD" << std::endl;
		glfwTerminate();
		return 0;
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, setResizeFallBack);
	/*-------------Setting up Opengl Objects---------------*/
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	/*----------------Shader Source Code---------------------*/
	char const *vertexShaderSource = R"(
	#version 330 core
	layout(location =0) in vec3 aPos;
	void main()
	{
		gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0f);
	}
	)";
	char const *fragmentShaderSource = R"(
	#version 330 core
	out vec4 fragColor;
	void main()
	{
	fragColor=vec4(1.0f,0.3f,0.45f,1.0f);
	}
	)";
	//---------------COMPILING ALL THE SHADERS_---------------//
	unsigned int vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	//---------------ERROR HANDLING FOR THE SHADERS-----------------//
	int success = 0;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
		std::cout << "ERROR IN VERTEX SHADER \t\t\t" << infoLog;
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR IN FRAGMENT SHADER \t\t\t" << infoLog;
	}
	//---------------------SHADER PROGRAM-------------------------//
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glLinkProgram(shaderProgram);
	
	glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR IN LINKING THE SHADER PROGRAM \t\t" <<infoLog<< std::endl;
	}
	//--------------------SETTING UP VAO CONFIGURATION---------------------//
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	

	while (!glfwWindowShouldClose(window))
	{
		inputBuffer(window);
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
void setResizeFallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0,0,width,height);
}
void inputBuffer(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		return;
	}
}