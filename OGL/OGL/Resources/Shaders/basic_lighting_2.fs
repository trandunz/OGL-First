#version 460 core

struct Material 
{
    sampler2D diffuse;
    sampler2D normal;
    sampler2D specular;
    float shininess;
}; 

struct DirLight 
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight 
{
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight 
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
in vec3 ViewPos;

out vec4 FragColor;

uniform DirLight dirLight;
uniform PointLight pointLights[20];
uniform SpotLight spotLight;
uniform Material material;

float near = 0.1f;
float far = 100.0f;

float linearizeDepth(float depth);
float logisticDepth(float depth, float steepness = 0.5f, float offset = 5.0f);
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    // properties
    //vec3 norm = normalize(texture(material.normal, TexCoords).xyz * 2.0f - 1.0f);
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(ViewPos - FragPos);
    
    // phase 1: directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    for (int i = 0; i < 20; i++)
    {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }
   
    // phase 3: spot light
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
    
    FragColor = vec4(result, 1.0);
} 

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords).r);

    if (texture(material.diffuse, TexCoords).a < 0.1 || texture(material.specular, TexCoords).a < 0.1)
        discard;

    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords).r);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords).r);
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    if (texture(material.diffuse, TexCoords).a < 0.1 || texture(material.specular, TexCoords).a < 0.1)
        discard;

    return (ambient + diffuse + specular);
}

float linearizeDepth(float depth)
{
    return (2.0 * near * far) / (far + near - (depth  * 2.0 -1.0) * (far - near));
}

float logisticDepth(float depth, float steepness = 0.8f, float offset = 1.0f)
{
    float zValue = linearizeDepth(depth);
    return (1/(1+exp(-steepness * (zValue - offset))));
}