#include "physics/Force.h"

Force::Force(const PhysicsBody *other) : _other_body(other) {}

Vector Force::calculate(const PhysicsBody &body) const {
	if (!_other_body || _other_body == &body)
		return Vector();

	Vector direction(body.position(), _other_body->position());
	double distance_squared = pow(direction.length(), 2);

	if (direction.isZero())
		return Vector();

	direction.normalize();

	// F = G * m1 * m2 / r^2
	double force_magnitude = Constants::GRAVITATIONAL_CONSTANT * body.mass() * _other_body->mass() / distance_squared;

	return direction * force_magnitude;
}
