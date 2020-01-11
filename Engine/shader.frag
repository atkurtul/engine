#version 460
out vec4 fragcolor;
in vec4 col;
in vec3 fpos;
in vec3 normal;
in vec2 tex;
uniform vec3 lpos;
uniform vec3 vpos;

uniform mat4 lightView;
uniform mat4 lightPrj;

layout(binding = 0) uniform sampler2D shadowMap;
layout(binding = 1) uniform sampler2D Texture;

float ShadowCalculation(vec4 fragPosLightSpace);

void main() 
{
	vec3 lightDir =  normalize(lpos - fpos);
	vec3 viewDir = normalize(vpos - fpos);

	float amb = 0.1;
	float diff = max(dot(normal, lightDir), 0.0);
	float spec = pow(max(dot(viewDir, reflect(-lightDir, normal)), 0), 64) * 0.5; 
    float shadow = ShadowCalculation(lightPrj * lightView * vec4(fpos, 1));

    vec3 lighting = vec3((amb + 1.0 - shadow) * (diff + spec));
    //fragcolor = vec4(lighting, 1) * col;
    fragcolor = texture(Texture, tex) * vec4(lighting, 1);
}

float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    float currentDepth = projCoords.z;
    vec3 dir = normalize(lpos - fpos);
    float bias = max(0.05 * (1.0 - dot(normal, dir)), 0.005);
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    if(projCoords.z > 1.0)
        shadow = 0.0;
    return shadow;
}