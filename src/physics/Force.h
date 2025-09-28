#pragma once

#include "utils/Constants.h"
#include "geometry/Vector.h"

class PhysicsBody;

class Force {
private:
	const PhysicsBody *_other_body;

public:
	Force(const PhysicsBody *other);
	Vector calculate(const PhysicsBody &body) const;
};
