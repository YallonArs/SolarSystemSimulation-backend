#pragma once

#include "physics/PhysicsBody.h"
#include "utils/Constants.h"

class Force {
private:
	const PhysicsBody *_other_body;

public:
	Force(const PhysicsBody *other);
	Vector calculate(const PhysicsBody &body) const;
};
