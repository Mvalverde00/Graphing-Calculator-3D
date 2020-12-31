#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 projectionView;


void main() {
  gl_Position = projectionView * vec4(pos, 1.0);
}
