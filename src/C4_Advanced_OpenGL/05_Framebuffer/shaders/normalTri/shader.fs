#version 330 core

in vec3 FragPos;
in vec3 FragNormal;

out vec4 FragColor;

uniform vec3 objColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {
  float ambientS = 0.1;
  vec3 ambientSum = ambientS * lightColor;

  float diffuseS = max(dot(normalize(FragNormal), normalize(lightPos - FragPos)), 0.0);
  vec3 diffuseSum = diffuseS * lightColor;

  float specStrength = 0.5;
  // Blinn-Phong 
  float specS = specStrength * pow(dot(normalize(viewPos - FragPos), normalize(normalize(lightPos - FragPos) + normalize(viewPos - FragPos))), 32);
  // Phong
  // vec3 reflectDir = reflect(-normalize(lightPos - FragPos), FragNormal);
  // float specS = specStrength * pow(max(dot(reflectDir, normalize(viewPos - FragPos)), 0.0), 32);
  vec3 specSum = specS * lightColor;

  vec3 result = (ambientSum + diffuseSum + specSum) * objColor;
  FragColor = vec4(result, 1.0f);
}