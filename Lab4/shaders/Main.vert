#version 460 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColour;
layout(location = 2) in vec3 vertexNormal;

out vec3 colour;
out vec3 normal;
out vec3 fragPosition;

uniform mat4 transformMatrix;
uniform mat4 modelMatrix;

void main() {
    colour = vertexColour;
    normal = mat3(transpose(inverse(modelMatrix))) * vertexNormal;
    fragPosition = vec3(modelMatrix * vec4(vertexPosition, 1.0));
    gl_Position = transformMatrix * vec4(vertexPosition, 1.0);
}