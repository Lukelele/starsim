#include "System.h"


//const double GRAVITATIONAL_CONSTANT = 6.674e-11;
const double GRAVITATIONAL_CONSTANT = 0.006;


System::System() {

}


void System::Add(Body &body) {
	bodies.push_back(&body);
	body.SetName("Planet" + std::to_string(bodies.size()));
}


void System::Orbit() {
	vector <vec3> sumForces;
	if (paused == false) {
		for (int i = 0; i < bodies.size(); i++) {
			sumForces.push_back(vec3());
			for (int j = 0; j < bodies.size(); j++) {
				if (i == j || bodies[i]->GetActive() == false || bodies[i]->GetActive() == false) {
					continue;
				}
				else {
					float GMM = GRAVITATIONAL_CONSTANT * bodies[i]->getMass() * bodies[j]->getMass() * gameSpeed;
					float distanceSquared = (bodies[j]->GetPosition().x - bodies[i]->GetPosition().x) * (bodies[j]->GetPosition().x - bodies[i]->GetPosition().x) + (bodies[j]->GetPosition().y - bodies[i]->GetPosition().y) * (bodies[j]->GetPosition().y - bodies[i]->GetPosition().y) + (bodies[j]->GetPosition().z - bodies[i]->GetPosition().z) * (bodies[j]->GetPosition().z - bodies[i]->GetPosition().z);
					vec3 direction = (bodies[j]->GetPosition() - bodies[i]->GetPosition());
					vec3 force = vec3();
					if (distanceSquared == 0) {
						force = vec3(0, 0, 0);
					}
					else {
						force = vec3(GMM, GMM, GMM) / distanceSquared * normalize(direction);
					}
					
					sumForces[i] += force;
				}
			}
		}
		for (int i = 0; i < bodies.size(); i++) {
			bodies[i]->SetAcceleration(sumForces[i] / bodies[i]->getMass(), gameSpeed);
		}
	}
}


void System::Pause() {
	previousVelocities.clear();
	for (int i = 0; i < bodies.size(); i++) {
		previousVelocities.push_back(bodies[i]->GetVelocity());
		bodies[i]->SetVelocity(vec3(0, 0, 0));
		paused = true;
	}
}


void System::Continue(float GameSpeed) {
	for (int i = 0; i < bodies.size(); i++) {
		bodies[i]->SetVelocity(previousVelocities[i] * GameSpeed);
		paused = false;
	}
}


void System::ChangeSpeed(float GameSpeed) {
	if (gameSpeed != GameSpeed) {
	//	Pause();
		gameSpeed = GameSpeed;
	//	Continue(gameSpeed);
	}
}


void System::Remove(int index) {
	bodies.erase(bodies.begin() + index);
}


void System::Clear() {
	bodies.clear();
}


float System::GetDistanceBetweenBodies(vec3 pos1, vec3 pos2) {
	return sqrt((pos2.x - pos1.x) * (pos2.x - pos1.x) + (pos2.y - pos1.y) * (pos2.y - pos1.y) * (pos2.z - pos1.z) * (pos2.z - pos1.z));
}

