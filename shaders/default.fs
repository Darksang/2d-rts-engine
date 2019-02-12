#version 330 core

out vec4 FragColor;

in vec3 Color;
in vec2 TexCoord;

// Texture sampler
uniform sampler2D Texture1;

void main() {
    FragColor = texture(Texture1, TexCoord) * vec4(Color, 1.0);
}