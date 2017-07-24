#version 410 core
#define maxLights 15

struct SceneData
{
  float gamma;
  float exposure;
  float fogDensity;
  vec3 fogColor;
};

struct LightData
{
  vec3 lightColor;
  vec3 lightPos;
  float lightStrength;
  float specularStrength;
  int isLight;
};

out vec4 color;
in vec2 texCoords;
in vec3 worldPos;
in vec3 normals;
in mat3 TBN;
in mat4 MV;
in mat4 V;

uniform vec3 camPos;
uniform vec3 lightColor;
uniform int hasNormalMap;
uniform SceneData sceneData;
uniform LightData lightData[maxLights];
uniform sampler2D texture;
uniform sampler2D normalMap;

vec4 getLight(LightData lightdata, vec3 eyedir, vec3 norms, vec3 worldPosition, vec4 texture, vec3 ambient, mat3 tangentSpace, vec3 lightDirection, int isNM)
{
  vec3 E = normalize(eyedir);

  vec3 N = norms;

  vec3 ambientTerm = vec3(0);
  vec3 diffuseTerm = vec3(0);
  vec3 specularTerm = vec3(0);
  vec3 L, H;

    L = normalize(lightDirection);
    H = normalize(E + L);
    ambientTerm += lightdata.lightColor;
    diffuseTerm += lightdata.lightColor * max(dot(L, N), 0);
    if (isNM > 0.5) {
      specularTerm += lightdata.specularStrength * 2.0 * lightdata.lightColor * pow(max(dot(H, N), 0), 32);
    } else {
      vec3 reflectDir = reflect(-lightDirection, norms);
      specularTerm += lightdata.specularStrength* lightdata.lightColor * pow(max(dot(E, reflectDir), 0), 32);
    }
  float distanceToLight = length(lightdata.lightPos - worldPos);
  float extinction = 100.0 / (1.1 * pow(distanceToLight, 2)) * lightdata.lightStrength;

  vec4 finishedLighting = vec4(texture) * vec4(ambientTerm * extinction + (diffuseTerm + specularTerm), 1);

  return finishedLighting;
}

void main(void)
{
  vec4 diffuseTexture = texture2D(texture, vec2(texCoords.x, 1-texCoords.y));
  color = vec4(diffuseTexture);
  vec3 normalmap = texture2D(normalMap, vec2(texCoords.x, 1-texCoords.y)).rgb * 2.0 - 1.0;
  vec3 ambient = vec3(0.09, 0.09, 0.09);
  vec4 result = vec4(diffuseTexture.rgb * ambient, diffuseTexture.a);

  for (int i = 0; i < maxLights; i++) {
    if (lightData[i].isLight == 1) {
      if (hasNormalMap == 1) {
        vec3 vertexInCamSpace = (MV * vec4(worldPos, 1.0)).xyz;
        vec3 eyeDir = TBN * normalize( -vertexInCamSpace);
        vec3 lightInCamSpace = (  MV * vec4(lightData[i].lightPos, 1.0)).xyz;
        vec3 lightDir = TBN * normalize((lightInCamSpace - vertexInCamSpace));
        result += getLight(lightData[i], eyeDir, normalmap, worldPos, diffuseTexture, ambient, TBN, lightDir, 1);
      } else {
        vec3 lightDir = normalize(lightData[i].lightPos - worldPos);
        result += getLight(lightData[i], camPos - worldPos, normals, worldPos, diffuseTexture, ambient, TBN, lightDir, 0);
      }
    }
  }
  if (sceneData.fogDensity != 0)
  {
    float fogFactor;
    float dist = length(camPos - worldPos);
    fogFactor = 1.0 /exp( (dist * sceneData.fogDensity)* (dist * sceneData.fogDensity));
    fogFactor = clamp( fogFactor, 0.0, 2.0 );
    result = mix(vec4(sceneData.fogColor,1), vec4(result), fogFactor);
  }
  vec3 mapped = vec3(1.0) - exp(-result.rgb * sceneData.exposure);
  mapped = pow(mapped, vec3(1.0 / sceneData.gamma));
  color = vec4(mapped,1);

}
