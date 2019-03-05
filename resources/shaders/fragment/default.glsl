#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D Texture1;

void main() {
    FragColor = texture(Texture1, TexCoords);
}