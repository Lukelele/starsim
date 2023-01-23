#pragma once
#include <vector>
#include <cmath>
#include "Body.h"

using std::vector;


class System
{
public:
	System();
	void Add(Body &body);
	void Remove(int index);
	float GetDistanceBetweenBodies(vec3 pos1, vec3 pos2);
	vector <Body*> GetBodies() { return bodies; }
	void Orbit();
	void Pause();
	void Continue(float GameSpeed = 1);
	void ChangeSpeed(float GameSpeed);
	void Clear();
	bool GetPaused() { return paused; }
private:
	vector <Body*> bodies;
	vector <vec3> previousVelocities;
	bool paused = false;
	float gameSpeed = 1;
};
 