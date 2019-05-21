#version 330 core

layout (location = 0) in vec2 Position;
layout (location = 1) in vec4 Color;
layout (location = 2) in float PointSize;

out vec4 OutColor;

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main() {
    gl_Position = ProjectionMatrix * ViewMatrix * vec4(Position, 0.0f, 1.0f);
    gl_PointSize = PointSize;
    OutColor = Color;
}