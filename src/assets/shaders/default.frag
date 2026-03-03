#version 330 core

in vec4 fragColor;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D uAlbedoTexture;

void main() {
    FragColor = texture(uAlbedoTexture, vec2(TexCoords.x, TexCoords.y * -1));
}