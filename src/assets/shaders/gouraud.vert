#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec2 TexCoords;
out vec3 Lighting;

uniform float uTime;
uniform vec2 uResolution;
uniform vec2 uMouse;

uniform mat4 uModel;
uniform mat4 uProjection;
uniform mat4 uView;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

void main() {
    gl_Position = uProjection * uView * uModel * vec4(position.xyz, 1.0);
    TexCoords = uv;

    vec3 mPosition = vec3(uModel * vec4(position, 1.0));
    vec3 mNormal = mat3(transpose(inverse(uModel))) * normal;

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(mNormal);
    vec3 lightDir = normalize(lightPos - mPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    Lighting = ambient + diffuse;
}