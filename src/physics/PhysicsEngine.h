#pragma once

#include <vector>

#include "physics/Force.h"

class PhysicsEngine {
public:
	PhysicsEngine() = default;
	void calculateForces(std::vector<PhysicsBody*>& bodies);

private:
	void calculatePairwiseForce(PhysicsBody* body1, PhysicsBody* body2);
};
