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
    sampler2D specularTexture;
    bool useAlbedoTexture;
    bool useSpecularTexture;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PhongLightResult {
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

PhongLightResult computeLighting(vec3 mPosition, vec3 mNormal) {
    PhongLightResult result;

    result.ambient = light.ambient * material.ambient;

    // diffuse
    vec3 norm = normalize(mNormal);
    vec3 lightDir = normalize(light.position - mPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    result.diffuse = light.diffuse * (diff * material.diffuse);

    // specular
    vec3 viewDir = normalize(camera.worldPosition - mPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    result.specular = light.specular * (spec * material.specular * (material.shininess / 1000));

    return result;
}

void main()
{

    vec3 mPosition = vec3(uModel * vec4(Position, 1.0));
    vec3 mNormal = mat3(transpose(inverse(uModel))) * Normal;

    PhongLightResult lightResult = computeLighting(mPosition, mNormal);
    vec3 lighting = lightResult.ambient + lightResult.specular + lightResult.diffuse;
    vec4 diffuse = vec4(lightResult.diffuse, 1.0);
    vec4 specular = vec4(lightResult.specular, 1.0);

    if (material.useAlbedoTexture)
    {
        diffuse *= texture(material.albedoTexture, TexCoords);
    }

    if (material.useSpecularTexture)
    {
        specular *= texture(material.specularTexture, TexCoords);
    }

    FragColor = vec4(lightResult.ambient + diffuse.rgb + specular.rgb, diffuse.a);
}