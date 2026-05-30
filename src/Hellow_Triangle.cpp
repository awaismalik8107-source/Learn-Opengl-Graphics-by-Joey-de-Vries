#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<iostream>

void frameBuffer_fallBack(GLFWwindow* window, int width, int height);
void InputBuffer(GLFWwindow* window);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	unsigned int VBO;
	float vertex[] = {
		-0.5f, -0.5f ,0.0f,
		 0.5f, -0.5  ,0.0f,
		 0.0f,  0.5f ,0.0f
	};
	//this is basically putting the 3D vertex z coordinate to 0 
	GLFWwindow* window = glfwCreateWindow(800, 600, "HELLO TRIANGLE", NULL, NULL);
	if (!window)
	{
		std::cout << "ERROR INITAILIZING THE WINDOW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR IN LOADING THE GLAD LIBRARY" << std::endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0,800,600);
	glfwSetFramebufferSizeCallback(window, frameBuffer_fallBack);

	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	/*
	1. Create a Vertex Buffer Object (VBO).

	2. Bind the VBO to the GL_ARRAY_BUFFER target.
	   Any operation on GL_ARRAY_BUFFER now affects this VBO.

	3. Copy the vertex data from CPU memory (vertex[])
	   into the GPU memory associated with the VBO.

	CPU RAM                          GPU VRAM
	--------                         --------
	vertex[]  --------copy---------> VBO

	GL_STATIC_DRAW tells OpenGL that the data
	will be uploaded once and used many times.
*/
	while (!glfwWindowShouldClose(window))
	{
		InputBuffer(window);
		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
void frameBuffer_fallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void InputBuffer(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		std::cout << "ESCAPE PRESSED" << std::endl;
		glfwSetWindowShouldClose(window, true);
	}
}