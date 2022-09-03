#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
mat3 normModel = transpose(inverse(mat3(model)));

void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    fragPos = vec3(model * vec4(aPos, 1.0));
    normal = normModel * aNormal;
    texCoord = aTexCoord;
}

#shader fragment
#version 330 core
struct Material
{
    sampler2D diffuse;
    sampler2D specular;

    float shininess;
};
struct SpotLight
{
    vec3 position, direction;
    vec3 ambient, diffuse, specular;
    float cosInner, cosOuter;
};

struct DirLight
{
    vec3 direction;
    vec3 ambient, diffuse, specular;
};

struct PointLight
{
    vec3 position;
    vec3 ambient, diffuse, specular;
    vec3 coefficients;
};

vec3 CalcDirLight(DirLight light);
vec3 CalcSpotLight(SpotLight light);
vec3 CalcPointLight(PointLight light);

vec3 CalcAmbient(vec3 ambient);
vec3 CalcDiffuse(vec3 diffuse, vec3 toLight);
vec3 CalcSpecular(vec3 specular, vec3 toLight);

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

out vec4 fragColour;

uniform Material material;
uniform vec3 viewPos;

const int N_POINT_LIGHTS = 4;
uniform PointLight pointLights[N_POINT_LIGHTS];
uniform DirLight dirLight;
uniform SpotLight spotLight;

vec3 norm = normalize(normal);
void main()
{    

    vec3 result = vec3(0.0);
    result += CalcDirLight(dirLight);
    result += CalcSpotLight(spotLight);
    for(int i = 0; i < N_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i]);
    fragColour = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light)
{
    vec3 ambient = CalcAmbient(light.ambient);
    vec3 diffuse = CalcDiffuse(light.diffuse, light.direction);
    vec3 specular = CalcSpecular(light.specular, light.direction);

    return ambient + diffuse + specular;
}

vec3 CalcSpotLight(SpotLight light)
{
    vec3 result = CalcAmbient(light.ambient);

    vec3 toLight = normalize(light.position - fragPos);
    float cosTheta = dot(-toLight, light.direction);
    float intensity = clamp((light.cosOuter - cosTheta) / (light.cosOuter - light.cosInner), 0.0, 1.0);

    if(intensity > 0.0)
    {
        vec3 diffuse = CalcDiffuse(light.diffuse, -toLight);
        vec3 specular = CalcSpecular(light.specular, -toLight);
        result += intensity * (diffuse + specular);
    }
    return result;
}

vec3 CalcPointLight(PointLight light)
{
    float d = length(fragPos - light.position);
    float intensity = 1.0 / (light.coefficients.x + light.coefficients.y * d + light.coefficients.z * d * d);

    vec3 ambient = CalcAmbient(light.ambient);

    vec3 direction = normalize(fragPos - light.position);
    vec3 diffuse = CalcDiffuse(light.diffuse, direction);
    vec3 specular = CalcSpecular(light.specular, direction);

    return intensity * (ambient + diffuse + specular);
}

vec3 CalcAmbient(vec3 ambient)
{
    return ambient * vec3(texture(material.diffuse, texCoord));
}

vec3 CalcDiffuse(vec3 diffuse, vec3 direction)
{
    float diff = max(dot(norm, -direction), 0.0);
    return diffuse = diffuse * (diff * vec3(texture(material.diffuse, texCoord)));
}

vec3 CalcSpecular(vec3 specular, vec3 direction)
{
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(direction, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    return specular * (spec * vec3(texture(material.specular, texCoord)));
}