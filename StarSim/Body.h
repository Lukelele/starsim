#pragma once
#include <string.h>
#include "Shape.h"
#include "Shader.h"

using namespace glm;
using std::string;


class Body
{
public:
	Body();
	Body(const char* objFilePath);
	Body(Shape &shape);

	void SetPosition(vec3 position);
	vec3 GetPosition() { return m_position; }
	void SetVelocity(vec3 velocity, float multiplier = 1);
	vec3 GetVelocity() { return m_velocity; }
	void SetAcceleration(vec3 acceleration, float multiplier = 1);
	vec3 GetAcceleration() { return m_acceleration; }
	void SetScale(float scale);
	float GetScale() { return m_scale; }
	void SetRotation(vec3 rotation, float rate = 1);
	vec3 GetRotation() { return m_rotation; }
	float GetRotationRate() { return m_rotationRate; }
	void SetMass(float mass);
	float getMass() { return m_mass; }
	void SetShape(Shape& shape) { m_shape = shape; }
	Shape* GetShape() { return &m_shape; }
	string GetName() { return m_name; }
	void SetName(string name) { m_name = name; }
	char GetType() { return m_type; }
	void SetType(char bodyType) { m_type = bodyType; }
	bool GetActive() { return m_active; }
	void SetActive(bool active) { m_active = active; }
	void Free();
	vec3 m_position;
	vec3 m_velocity;
	vec3 m_acceleration;
	vec3 m_rotation;
	float m_rotationRate;
	float m_scale;
	float m_mass;

protected:
	Shape m_shape;
	string m_name;
	char m_type;
	bool m_active = true;
};
