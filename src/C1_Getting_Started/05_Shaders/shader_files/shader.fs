#version 330 core
out vec4 FragColor;
in vec3 myPosition;

void main()
{
    // FragColor = vec4(0.4666666667f, 0.2f, 0.5529411765f, 1.0f);
    FragColor = vec4(myPosition, 1.0);
} 
