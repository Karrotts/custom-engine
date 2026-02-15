#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoords;

out vec4 fragColor;
out vec2 TexCoords;

uniform float uTime;
uniform vec2 uResolution;
uniform vec2 uMouse;

void main() {
    float res = uResolution.x / uResolution.y;
    gl_Position = vec4(position.x / res, position.yz, 1.0);
    fragColor = vec4(color.xyz, 1.0);
    TexCoords = texCoords;
}