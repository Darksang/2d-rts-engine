#version 330 core

layout (location = 0) in vec4 Vertex;

out vec2 TexCoords;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main() {
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(Vertex.xy, 0.0f, 1.0f);
    TexCoords = Vertex.zw;
}