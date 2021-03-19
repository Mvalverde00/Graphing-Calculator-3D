#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

uniform mat4 projectionView;

out vec3 vertColor;


void main() {
  gl_Position = projectionView * vec4(pos, 1.0);
  vertColor = color;
}
