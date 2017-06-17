#version 410 core
#define maxLights 15

struct SceneData
{
  float gamma;
  float exposure;
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

uniform vec3 camPos;
uniform vec3 lightColor;
uniform int hasNormalMap;
uniform SceneData sceneData;
uniform LightData lightData[maxLights];
uniform sampler2D texture;
uniform sampler2D normalMap;

vec4 getLight(LightData lightdata, vec3 camPosition, vec3 norms, vec3 worldPosition, vec4 texture, vec3 ambient)
{
  vec3 norm = normalize(norms);
  vec3 lightDir = normalize(lightdata.lightPos - worldPosition);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightdata.lightStrength * lightdata.lightColor;

  float specularStrength = lightdata.specularStrength;
  vec3 viewDir = normalize(camPosition - worldPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = specularStrength * spec * lightdata.lightColor;

  float distanceToLight = length(lightdata.lightPos - worldPosition);

  float extinction = 100.0 / (1.1 * pow(distanceToLight, 2)) * lightdata.lightStrength;

  return vec4(texture.rgb * (ambient + extinction * (diffuse + specular)), texture.a);
}

void main(void)
{
  vec4 diffuseTexture = texture2D(texture, vec2(texCoords.x, 1-texCoords.y));
  color = vec4(diffuseTexture);
  vec3 normalmap = normalize(texture2D(normalMap, vec2(texCoords.x, 1-texCoords.y)).rgb * 2.0 - 1.0);
  vec3 ambient = vec3(0.09, 0.09, 0.09);
  vec4 result = vec4(diffuseTexture.rgb * ambient, diffuseTexture.a);

  for (int i = 0; i < maxLights; i++) {
    if (lightData[i].isLight == 1) {
      if (hasNormalMap == 1) {
        result += getLight(lightData[i], camPos, normalmap, worldPos, diffuseTexture, ambient);
      } else {
        result += getLight(lightData[i], camPos, normals, worldPos, diffuseTexture, ambient);
      }
    }
  }

  vec3 mapped = vec3(1.0) - exp(-result.rgb * sceneData.exposure);
  mapped = pow(mapped, vec3(1.0 / sceneData.gamma));
  color = vec4(mapped,1);

}
