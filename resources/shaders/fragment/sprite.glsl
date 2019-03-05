#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

// Texture sampler
uniform sampler2D Sprite;
uniform vec3 Color;

void main() {
    FragColor = vec4(Color, 1.0) * texture(Sprite, TexCoords);
}