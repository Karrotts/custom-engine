#version 330 core

struct Camera {
    mat4 projection;
    mat4 view;
    vec3 worldPosition;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    sampler2D albedoTexture;
    bool useAlbedoTexture;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 Position;

out vec4 FragColor;

uniform Material material;
uniform Light light;
uniform Camera camera;

uniform mat4 uModel;

vec3 computeLighting(vec3 mPosition, vec3 mNormal) {
    vec3 ambient = light.ambient * material.ambient;

    // diffuse
    vec3 norm = normalize(mNormal);
    vec3 lightDir = normalize(light.position - mPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // specular
    vec3 viewDir = normalize(camera.worldPosition - mPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    return ambient + diffuse;
}

void main()
{
    vec4 color = vec4(1.0);
    vec3 mPosition = vec3(uModel * vec4(Position, 1.0));
    vec3 mNormal = mat3(transpose(inverse(uModel))) * Normal;

    vec3 lighting = computeLighting(mPosition, mNormal);

    if (material.useAlbedoTexture)
    {
        color = texture(material.albedoTexture, TexCoords);
    }

    FragColor = vec4(color.rgb * lighting, color.a);
}