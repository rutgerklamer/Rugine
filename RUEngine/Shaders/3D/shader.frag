#version 410 core

out vec4 color;
in vec2 texCoords;
in vec3 worldPos;
in vec3 normals;

uniform vec3 lightPos;
uniform vec3 camPos;
uniform vec4 lightColor;
uniform sampler2D texture;

void main(void)
{
  vec4 diffuseTexture = texture2D(texture, texCoords);

  if (length(camPos)  > 0.001) {
    vec3 ambient = vec3(0.09, 0.09, 0.09);

    vec4 result = vec4(diffuseTexture.rgb * ambient, diffuseTexture.a);
    vec3 norm = normalize(normals);
  	vec3 lightDir = normalize(lightPos - worldPos);
  	float diff = max(dot(norm, lightDir), 0.0);
  	vec3 diffuse = diff * lightColor.a * lightColor.rgb;

  	float specularStrength = 0.8;
  	vec3 viewDir = normalize(camPos - worldPos);
  	vec3 reflectDir = reflect(-lightDir, norm);
  	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  	vec3 specular = specularStrength * spec * lightColor.a * lightColor.rgb;

  	float distanceToLight = length(lightPos - worldPos);

  	float extinction = 1.0 / (1.1 * pow(distanceToLight, 2));

  	result += vec4(diffuseTexture.rgb * (ambient + extinction * (diffuse + specular)), diffuseTexture.a);
    color = result;
  } else {
    color = vec4(diffuseTexture);
  }
}
