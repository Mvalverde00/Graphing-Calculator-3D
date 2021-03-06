#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 projectionView;

out vec3 vertPos;


void main() {
  gl_Position = projectionView * vec4(pos, 1.0);
  vertPos = pos;
}
