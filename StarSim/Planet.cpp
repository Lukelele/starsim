#include "Planet.h"


Planet::Planet(const char* objFilePath) {
	m_shape.LoadOBJ(objFilePath);
	SetPosition(vec3(0, 0, 0));
	SetRotation(vec3(0, 1, 0), 0);
	SetScale(1);
	SetMass(1);
}

Planet::Planet() {
	SetPosition(vec3(0, 0, 0));
	SetRotation(vec3(0, 1, 0), 0);
	SetScale(1);
	SetMass(1);
}
