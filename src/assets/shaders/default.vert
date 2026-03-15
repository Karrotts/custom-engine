#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec2 TexCoords;

uniform float uTime;
uniform vec2 uResolution;
uniform vec2 uMouse;

uniform mat4 uModel;
uniform mat4 uProjection;
uniform mat4 uView;

void main() {
    gl_Position = uProjection * uView * uModel * vec4(position.xyz, 1.0);
    TexCoords = uv;
}