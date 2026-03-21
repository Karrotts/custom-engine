#version 330 core

struct Camera {
    mat4 projection;
    mat4 view;
    vec3 worldPosition;
};

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec2 TexCoords;
out vec3 Normal;
out vec3 Position;

uniform mat4 uModel;
uniform Camera camera;

// ---- SHADER DEFAULTS ----
uniform float uTime;
uniform vec2 uResolution;
uniform vec2 uMouse;

void main() {
    gl_Position = camera.projection * camera.view * uModel * vec4(position.xyz, 1.0);
    TexCoords = uv;
    Normal = normal;
    Position = position;
}