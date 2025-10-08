#pragma once

#include "geometry/Vector.h"
#include "utils/Constants.h"

class PhysicsBody;

class Force {
public:
	Force(const PhysicsBody *other);
	Vector calculate(const PhysicsBody &body) const;

private:
	const PhysicsBody *_other_body;
};
