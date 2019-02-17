#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

// Texture sampler
uniform sampler2D Texture1;

void main() {
    FragColor = texture(Texture1, TexCoord);
}