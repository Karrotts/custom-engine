#version 330 core

in vec4 fragColor;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D uAlbedoTexture;
uniform vec4 uAlbedoColor;
uniform bool uUseAlbedoTexture;

void main()
{
    vec4 color = uAlbedoColor;

    if (uUseAlbedoTexture)
    {
        vec4 tex = texture(uAlbedoTexture, TexCoords);
        color = tex * uAlbedoColor;
    }

    FragColor = color;
}