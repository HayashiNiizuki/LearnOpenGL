#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // FragColor = mix(texture(texture1, vec2(TexCoord[0] / 1, TexCoord[1] / 1)), texture(texture2, TexCoord), 0.5);
    FragColor = texture(texture2, TexCoord);
}