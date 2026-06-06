//#define GLFW_INCLUDE_NONE
//#include<GLFW/glfw3.h>
//#include<glad/glad.h>
//#include<iostream>
//
//void frameBuffer_fallBack(GLFWwindow* window, int width, int height);
//void InputBuffer(GLFWwindow* window);
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	
//	unsigned int VBO;
//	float vertex[] = {
//		-1.0f, -0.5f ,0.0f,		1.0f,0.0f,0.0f,
//		 0.5f, -0.5  ,0.0f,		0.0f,1.0f,0.0f,
//		 0.0f,  0.5f ,0.0f,		0.0f,0.0f,1.0f
//	};
//	unsigned int VAO;
//	
//	//this is basically putting the 3D vertex z coordinate to 0 
//	GLFWwindow* window = glfwCreateWindow(800, 600, "HELLO TRIANGLE", NULL, NULL);
//	if (!window)
//	{
//		std::cout << "ERROR INITAILIZING THE WINDOW" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwMakeContextCurrent(window);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "ERROR IN LOADING THE GLAD LIBRARY" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glViewport(0, 0,800,600);
//	glfwSetFramebufferSizeCallback(window, frameBuffer_fallBack);
//	glGenVertexArrays(1, &VAO);
//
//	glBindVertexArray(VAO);
//
//	glGenBuffers(1,&VBO);
//
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
//
//	/*#######---------SHADERS-----------########*/
//	const char* vertexShaderSource =R"(
//	#version 330 core
//	layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
//	layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
//  
//	out vec3 ourColor; // output a color to the fragment shader
//	
//	void main()
//	{
//		gl_Position = vec4(aPos, 1.0);
//		ourColor = aColor; // set ourColor to the input color we got from the vertex data
//	}     
//	)";
//	unsigned int vertexShader;
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//	const char* fragmentShaderSource = R"(
//		#version 330 core
//		out vec4 FragColor;
//		in vec3 ourColor;
//		uniform vec4 colorChange;
//		void main()
//		{
//		FragColor=colorChange;
//		}
//		)";
//	unsigned int fragmentShader;
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//
//
///*################-----------SHADER ERROR HANDLER-----------###################*/
//	int successVertexShader;
//	char infologVertex[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertexShader);
//	//get the complile status;
//	if (!successVertexShader)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infologVertex);
//		std::cout << "ERRO IN COMPILING THE VERTEX SHADER" << infologVertex << std::endl;
//	}
//
//	int successFragmentShader;
//	char infologFramgent[512];
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragmentShader);
//	if (!successFragmentShader)
//	{
//		glGetShaderInfoLog(fragmentShader, 512, NULL, infologFramgent);
//		std::cout << "ERROR IN COMPILING THE FRAGMENT SHADER:\t" << infologFramgent << std::endl;
//	}
//
//	/*####---------Shader Program--------###*/
//	unsigned int shaderProgram;
//	shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	int successShaderProgram;
//	char infoLogProgram[512];
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successShaderProgram);
//	if (!successShaderProgram)
//	{
//		glGetProgramInfoLog(shaderProgram,512,NULL,infoLogProgram);
//		std::cout << "ERROR DURING THE LINKING OF THE SHADER PROGRAM" << std::endl;
//	}
//	/*
//	#----------------setting up the vertex data for the the GPU---------#
//	*/
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * (sizeof(float)), (void*)0);
//	glad_glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glad_glEnableVertexAttribArray(1);
//	/*
//	+++++++++++++++++------VAO(Vertex Array Object)-------++++++++++++++++
//	*/
//
//
//	glUseProgram(shaderProgram);
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	while (!glfwWindowShouldClose(window))
//	{
//		InputBuffer(window);
//		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		float timeValue = glfwGetTime();
//		float valuer = ((sin(timeValue) / 2.0f) + 0.5f);
//		float valueg = ((sin(timeValue-1.0) / 2.0f) + 0.5f);
//		float valueb = ((sin(timeValue-0.5) / 2.0f) + 0.5f);
//		float uniformLocation = glGetUniformLocation(shaderProgram,"colorChange");
//		glUniform4f(uniformLocation,valuer,valueg,valueb,1.0f);
//
//		glUseProgram(shaderProgram);
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//
//	}
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteProgram(shaderProgram);
//	glfwTerminate();
//	return 0;
//}
//void frameBuffer_fallBack(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//void InputBuffer(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//	{
//		std::cout << "ESCAPE PRESSED" << std::endl;
//		glfwSetWindowShouldClose(window, true);
//	}
//}