#version 330 core

out vec4 FragColor;

uniform mat4 projectionView;

void main() {
  FragColor = vec4(0.0, 0.0, 1.0, 1.0);
}
