#version 410 core

in vec3 normals;
in vec4 positions;

out vec4 fragmentColour;

uniform vec3 u_lightLocation;
uniform float u_ambientLight;
uniform vec4 u_colour;


void main() {
	vec3 lightVector = normalize(u_lightLocation - vec3(positions));

	float lightIntensity = clamp(dot(lightVector, normals), 0, 1);

	fragmentColour = clamp(lightIntensity * u_colour + u_ambientLight, 0, 1);
}
