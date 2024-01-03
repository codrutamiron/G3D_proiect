#version 330 core
in vec3 aPos;


out vec4 pos;

void main()
{
	pos = vec4(aPos, 1.0);
}