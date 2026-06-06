#version 330 core
	in vec4 ourColor;
	in vec2 textureCoord;

	out vec4 Fragcolor;
	
	uniform sampler2D ourTexture;
	void main ()
	{
	Fragcolor=texture(ourTexture,textureCoord)*ourColor;
	}