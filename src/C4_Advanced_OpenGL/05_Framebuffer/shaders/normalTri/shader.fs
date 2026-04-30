#version 330 core

in vec3 FragPos;
in vec3 FragNormal;

out vec4 FragColor;

uniform vec3 objColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Material material;

void main() {
  vec3 ambientSum = material.ambient * lightColor;

  float diffuseS = max(dot(normalize(FragNormal), normalize(lightPos - FragPos)), 0.0);
  vec3 diffuseSum = diffuseS * lightColor * material.diffuse;

  // Blinn-Phong 
  float specS = pow(dot(normalize(viewPos - FragPos), normalize(normalize(lightPos - FragPos) + normalize(viewPos - FragPos))), material.shininess);
  // Phong
  // vec3 reflectDir = reflect(-normalize(lightPos - FragPos), FragNormal);
  // float specS = pow(max(dot(reflectDir, normalize(viewPos - FragPos)), 0.0), material.shininess);
  vec3 specSum = specS * lightColor * material.specular;

  vec3 result = (ambientSum + diffuseSum + specSum) * objColor;
  FragColor = vec4(result, 1.0f);
}