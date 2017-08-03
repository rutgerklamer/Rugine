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
  float extinction;
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
uniform float time;
uniform vec3 Color;

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
  float extinction;
  if (lightdata.extinction > 0) {
    extinction = 0.0;
  } else {
    extinction = 100.0 / (1.1 * pow(distanceToLight, 2)) * lightdata.lightStrength;
  }

  vec4 finishedLighting = vec4(texture) * vec4(ambientTerm * extinction + (diffuseTerm + specularTerm), 1);

  return finishedLighting;
}

vec4 permute(vec4 x){return mod(((x*34.0)+1.0)*x, 289.0);}
vec4 taylorInvSqrt(vec4 r){return 1.79284291400159 - 0.85373472095314 * r;}
vec3 fade(vec3 t) {return t*t*t*(t*(t*6.0-15.0)+10.0);}

float cnoise(vec3 P){
  vec3 Pi0 = floor(P); // Integer part for indexing
  vec3 Pi1 = Pi0 + vec3(1.0); // Integer part + 1
  Pi0 = mod(Pi0, 289.0);
  Pi1 = mod(Pi1, 289.0);
  vec3 Pf0 = fract(P); // Fractional part for interpolation
  vec3 Pf1 = Pf0 - vec3(1.0); // Fractional part - 1.0
  vec4 ix = vec4(Pi0.x, Pi1.x, Pi0.x, Pi1.x);
  vec4 iy = vec4(Pi0.yy, Pi1.yy);
  vec4 iz0 = Pi0.zzzz;
  vec4 iz1 = Pi1.zzzz;

  vec4 ixy = permute(permute(ix) + iy);
  vec4 ixy0 = permute(ixy + iz0);
  vec4 ixy1 = permute(ixy + iz1);

  vec4 gx0 = ixy0 / 7.0;
  vec4 gy0 = fract(floor(gx0) / 7.0) - 0.5;
  gx0 = fract(gx0);
  vec4 gz0 = vec4(0.5) - abs(gx0) - abs(gy0);
  vec4 sz0 = step(gz0, vec4(0.0));
  gx0 -= sz0 * (step(0.0, gx0) - 0.5);
  gy0 -= sz0 * (step(0.0, gy0) - 0.5);

  vec4 gx1 = ixy1 / 7.0;
  vec4 gy1 = fract(floor(gx1) / 7.0) - 0.5;
  gx1 = fract(gx1);
  vec4 gz1 = vec4(0.5) - abs(gx1) - abs(gy1);
  vec4 sz1 = step(gz1, vec4(0.0));
  gx1 -= sz1 * (step(0.0, gx1) - 0.5);
  gy1 -= sz1 * (step(0.0, gy1) - 0.5);

  vec3 g000 = vec3(gx0.x,gy0.x,gz0.x);
  vec3 g100 = vec3(gx0.y,gy0.y,gz0.y);
  vec3 g010 = vec3(gx0.z,gy0.z,gz0.z);
  vec3 g110 = vec3(gx0.w,gy0.w,gz0.w);
  vec3 g001 = vec3(gx1.x,gy1.x,gz1.x);
  vec3 g101 = vec3(gx1.y,gy1.y,gz1.y);
  vec3 g011 = vec3(gx1.z,gy1.z,gz1.z);
  vec3 g111 = vec3(gx1.w,gy1.w,gz1.w);

  vec4 norm0 = taylorInvSqrt(vec4(dot(g000, g000), dot(g010, g010), dot(g100, g100), dot(g110, g110)));
  g000 *= norm0.x;
  g010 *= norm0.y;
  g100 *= norm0.z;
  g110 *= norm0.w;
  vec4 norm1 = taylorInvSqrt(vec4(dot(g001, g001), dot(g011, g011), dot(g101, g101), dot(g111, g111)));
  g001 *= norm1.x;
  g011 *= norm1.y;
  g101 *= norm1.z;
  g111 *= norm1.w;

  float n000 = dot(g000, Pf0);
  float n100 = dot(g100, vec3(Pf1.x, Pf0.yz));
  float n010 = dot(g010, vec3(Pf0.x, Pf1.y, Pf0.z));
  float n110 = dot(g110, vec3(Pf1.xy, Pf0.z));
  float n001 = dot(g001, vec3(Pf0.xy, Pf1.z));
  float n101 = dot(g101, vec3(Pf1.x, Pf0.y, Pf1.z));
  float n011 = dot(g011, vec3(Pf0.x, Pf1.yz));
  float n111 = dot(g111, Pf1);

  vec3 fade_xyz = fade(Pf0);
  vec4 n_z = mix(vec4(n000, n100, n010, n110), vec4(n001, n101, n011, n111), fade_xyz.z);
  vec2 n_yz = mix(n_z.xy, n_z.zw, fade_xyz.y);
  float n_xyz = mix(n_yz.x, n_yz.y, fade_xyz.x);
  return 2.2 * n_xyz;
}

void main(void)
{
  vec4 diffuseTexture;
  if (Color.r + Color.g + Color.b == 0)
  {
    diffuseTexture = texture2D(texture, texCoords);
  } else {
    diffuseTexture = vec4(vec3(Color.r, Color.g, Color.b),1);
  }

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
    float fog = cnoise(vec3(worldPos + vec3(time * 3)) / 4.0f);
    fogFactor = 1.0 /exp( (dist  * ( sceneData.fogDensity + (fog / 35)))* (dist  * (sceneData.fogDensity + (fog / 35))));
    fogFactor = clamp( fogFactor, 0.0, 1.0 );

    result = mix(vec4(sceneData.fogColor,1), vec4(result), fogFactor);
  }
  vec3 mapped = vec3(1.0) - exp(-result.rgb * sceneData.exposure);
  mapped = pow(mapped, vec3(1.0 / sceneData.gamma));
  color = vec4(mapped,1);

}
