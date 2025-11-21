#version 460 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;

out vec3 color;

uniform mat4 modelMat;
uniform mat4 projectionMat;

void main()
{
    color = vertex_color;
    gl_Position = projectionMat * modelMat * vec4(vertex_position,1);
}