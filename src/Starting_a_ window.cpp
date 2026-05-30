//#include<glad/glad.h>
///*
//Including for the graphic api libaray(OpenGl Loader /Gl extension Loader) comes before including
//the context and window library also called Windowing libraies
//
//To prevent compilation errors caused by macro redefination and header conflict
//*/
//#include<glfw/glfw3.h>
//


#define GLFW_INCLUDE_NONE
//this will disable the automatic system openGl inclusion
#include<GLfW/glfw3.h>
//Windowing Library
#include<GLAD/glad.h>
//Loader Library making it safer
#include<iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void proccesInput(GLFWwindow* window);

int main()
{
	glfwInit();
	//initate the glfw windowing libraries
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	/*the set the hints for the next call to the glfwCreateWindow.
	these hint could be changed to defualt by using glfwDefaultWindowHints.
	
	Syntax:------void glfwWindowHint(int hint,int value)-------------------

	*/

	/*
	set the maxiumum version for the opengl context
	*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	/*
	set the min version for the opengl context
	*/
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/*
	Set the opengl profile to modern opengl setting.
	GLfW_OPENGL_PROFILE is basicaly a enum ;
	*/

	GLFWwindow* window = glfwCreateWindow(800, 600, "Creating_the_Window",NULL,NULL);
	if (window == NULL)
	{
		std::cout << "failed to create the GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//this is basically the automatic version of lecture no 1
		std::cout << "Failed to initailize the GLAD" << std::endl;
		return -1;
	}
	glViewport(0,0,800,600);
	/*set up a view port for the project like a 2d graph system
	bottom left is the 0,0.

	syntax:-------------glViewport(glintx,glint y,glint width,glint height)-------------------;
	
	*/
	//Now lets fixed the resizing window lets create a calling function ;

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//will tell the window that call this function ever time the size is 
	//changed inside the buffer;

	//we initailizer or register every call back funtion before the main loop/render loop 

	/*###########################----------------RenderLoop------------####################################*/
	
	while (!glfwWindowShouldClose(window))
	{
		//at start of each loop check weather the window is instructed to close
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//rbga
		glClear(GL_COLOR_BUFFER_BIT);
		proccesIzasAnput(window);
		glfwSwapBuffers(window);
		/*
		->replace the current frame with the buffer frame;
		These buffers are also called front buffer and back buffer
		*/
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0,0,width, height);
}
void proccesInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		std::cout << ""<<std::endl;
		glfwSetWindowShouldClose(window,true);
	}

}

/*###########--------PREFERED SYNTAX-----------#############*/

/*
// render loop
while(!glfwWindowShouldClose(window))
{
	// input
	processInput(window);

	// rendering commands here
	...

	// check and call events and swap the buffers
	glfwPollEvents();
	glfwSwapBuffers(window);
}

*/