#pragma once

#include <vector>

#include "geometry/Point.h"
#include "geometry/Vector.h"
#include "physics/PhysicsBody.h"

class Integrator {
public:
	Integrator() = default;
	void integrate(std::vector<PhysicsBody *> &bodies, double deltaTime);

private:
	struct Derivative {
		Vector dx;
		Vector dv;
	};

	Derivative evaluate(PhysicsBody &body, const PhysicsBody::State &initial_state, double dt, const Derivative &derivative);
};
