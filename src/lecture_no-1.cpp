#include<iostream>
#include<GLFW/glfw3.h>
#include<glad/glad.h>

/*
GLFW is used to start initaie the windows as well as the context of the graphic card
so the Question is what is a context window?

Basically it is a gpu configuration which contains the gpu settings for the current frame.
for Example we have a setting in gpu name color. So the gpu need a configuration change in color 

Once the context is established we need a secondary library to manage the gpu apis (opengl apis).Libraries like 
GLFW SDL2 and SFML usually are used to auto manage the graphic settings while for full control we usually use api like opengl
which are managed by libraries like GLAD and GLEW, provided context window is already established.

context is a gpu configuration which contains gpu settings for the current frame
*/

void Lecture_no_1()
{
	typedef void (*GL_GENBUFFER)(GLsizei, GLuint*);
/*
	type create an other alias for the new type of data name GLbuffer.
	so  it is a pointer pointing to the function 
	that 

	takes GLsizei and gluint and 
	return the void return

	and itself is a pointer function
*/
	GL_GENBUFFER glad_glGenBuffers = (GL_GENBUFFER)glfwGetProcAddress("glGenBuffers");
	//this will create a new tyoe if functuin that can now be called .
	/*
	Concepts used are /

	#TypeCasting to convert the the return type into 
	usable data type for the GL_GENBUFFER

	#glProc address basically means give me the address of the
	OpenGLfunction name glGenBuffers that belongs to the current context
	*/
	unsigned int buffer;
	//this is the ID of the buffer
	/*
	each object created need an address or a value that we can use to point to the original object 
	similar to indexs
	*/
	glad_glGenBuffers(1, &buffer);
	return;

}