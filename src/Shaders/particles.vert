#version 430

layout (location = 0) in vec4 AttractorPosition;
layout (location = 1) in vec4 AttractorVelocity;

out vec4 velocity;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main()
{
    gl_Position = MVP * AttractorPosition;
    velocity = AttractorVelocity;
}
