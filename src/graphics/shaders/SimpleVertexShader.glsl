#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 color;

out vec4 vertexColor;

void main()
{
    gl_Position = vec4(aPos);
    vertexColor = vec4(color.x, color.y, color.z, 1.0);
}