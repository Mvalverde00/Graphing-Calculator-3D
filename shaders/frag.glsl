#version 330 core

in vec3 vertPos;

out vec4 FragColor;

uniform mat4 projectionView;

void main() {
  FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
