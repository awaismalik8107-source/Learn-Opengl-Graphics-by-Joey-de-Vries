#define GLFW_INCLUDE_NONE
#include<iostream>
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Shader.h"

void resizeFallBack(GLFWwindow* window, int width, int height);
void shaderErrorHandling(const unsigned int& shader);
void ProgramError(unsigned int& program);
void pressEvent(GLFWwindow* window, float& x, float& y, float& z);
int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Texture", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (!window)
	{
		std::cout << "ERROR ESTABLISHING THE WINDOW" << std::endl;
	}
	float vertex[] = {
	-0.5f,-0.5f,0.0f,	1.0f,0.0f,0.0f,1.0f,  0.0f,0.0f,
	 0.5f,-0.5f,0.0f,	0.0f,1.0f,0.0f,1.0f,  1.0f,0.0f,
	 0.0f,0.0f,0.01f,	0.0f,0.0f,1.0f,1.0f,  0.0f,1.0f
	};

	unsigned int VAO, VBO;
	int width, height, nrChannels;
	unsigned char* data = stbi_load("img/wall.jpg", &width, &height, &nrChannels, 0);
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
	glfwSetFramebufferSizeCallback(window, resizeFallBack);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	Shader ourShader(
		"Shaders/transformation.vert",
		"Shaders/transformation.frag"
	);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);

	
	float x = 1.0;
	float y = 1.0;
	float z = 1.0;
	while (!glfwWindowShouldClose(window))
	{
		pressEvent(window, x,y,z);
		glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glm::mat4 trans = glm::mat4(1.0f);
		//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 0.0));
		trans = glm::scale(trans, glm::vec3(x, y, z));

		
		unsigned int tranformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(tranformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		ourShader.use();
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
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Shader Error" << infoLog << std::endl;
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
void pressEvent(GLFWwindow* window, float& x, float& y, float& z)
{
	float increament = 0.01;
	
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		x += increament;
		y += increament;
		z += increament;
		std::cout << x << " " << y << " " << z << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		x -= increament;
		y -= increament;
		z -= increament;
		std::cout << x << " " << y << " " << z << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		x += increament;
		std::cout << x << " " << y << " " << z << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		x += increament;
		std::cout << x << " " << y << " " << z << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		x -= increament;
		std::cout << x << " " << y << " " << z << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		z += increament;
		std::cout << x << " " << y << " " << z << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		z -= increament;
		std::cout << x << " " << y << " " << z << std::endl;
	}

}
