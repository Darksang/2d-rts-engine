#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

// Texture sampler
uniform sampler2D Sprite;

void main() {
    FragColor = texture(Sprite, TexCoords);
}