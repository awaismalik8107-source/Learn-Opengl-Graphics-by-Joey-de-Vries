#version 330 core

layout(location = 0) in vec3 aPosx;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTextCoord;


out vec4 ourColor;
out vec2 textureCoord;

uniform mat4 transform;//matrix with 4x4 order
void main()
{
    gl_Position=transform*vec4(aPosx,1.0f);
	ourColor=aColor;
	textureCoord=aTextCoord;		
}