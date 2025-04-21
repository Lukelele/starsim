#include "Body.h"


Body::Body() {
	SetPosition(vec3(0, 0, 0));
	SetRotation(vec3(0, 1, 0), 0);
	SetScale(1);
	SetMass(1);
}


Body::Body(const char* objFilePath)
	:m_shape(Shape())
{
	m_shape.LoadOBJ(objFilePath);
	m_shape.BindVertices();
	SetPosition(vec3(0, 0, 0));
	SetRotation(vec3(0, 1, 0), 0);
	SetScale(1);
	SetMass(1);
}

Body::Body(Shape &shape)
{
	m_shape = shape;
	SetPosition(vec3(0, 0, 0));
	SetRotation(vec3(0, 1, 0), 0);
	SetScale(1);
	SetMass(1);
}

void Body::SetPosition(vec3 position)
{
	m_position = position;
}

void Body::SetVelocity(vec3 velocity, float multiplier)
{
	m_velocity = velocity;
	SetPosition(GetPosition() + (velocity * vec3(multiplier)));
}

void Body::SetAcceleration(vec3 acceleration, float multiplier) {
	m_acceleration = acceleration;
	SetVelocity(GetVelocity() + acceleration, multiplier);
}

void Body::SetRotation(vec3 rotation, float rate) {
	m_rotation = rotation;
	m_rotationRate = rate;
}

void Body::SetScale(float s)
{
	m_scale = s;
}

void Body::SetMass(float mass)
{
	m_mass = mass;
}

void Body::Free() {
	m_shape.Free();
	SetActive(false);
}
