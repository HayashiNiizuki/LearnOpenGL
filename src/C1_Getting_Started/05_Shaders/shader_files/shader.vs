#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 myPosition;
uniform float offset;

void main()
{
    // gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0);
    gl_Position = vec4(aPos, 1.0);
    myPosition = aPos;
}
