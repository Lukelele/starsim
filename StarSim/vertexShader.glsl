#version 410 core

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec3 vertexNormal;

out vec3 normals;
out vec4 positions;

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_rotationMatrix;
uniform mat4 u_translationMatrix;
uniform mat4 u_cameraTranslationMatrix;
uniform mat4 u_scaleMatrix;


void main() {
    normals = normalize(vec3( u_rotationMatrix * u_scaleMatrix * vec4(vertexNormal, 1)));
    positions = u_translationMatrix * u_rotationMatrix * u_scaleMatrix * vec4(vertexPosition, 1);
    gl_Position = u_projectionMatrix * u_viewMatrix * u_translationMatrix * u_rotationMatrix * u_scaleMatrix * vec4(vertexPosition, 1);
}
