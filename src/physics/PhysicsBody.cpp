#include "PhysicsBody.h"
#include "utils/Logger.h"

PhysicsBody::PhysicsBody(const std::string &name, double mass, const State &state) 
	: _name(name), _mass(mass), _state(state) {}

void PhysicsBody::addForce(Force *force) {
	_applied_forces.push_back(force);
}

void PhysicsBody::clearForces() {
	_applied_forces.clear();
}

Vector PhysicsBody::calculateTotalForce() const {
	Vector total_force;
	for (const auto force : _applied_forces)
		total_force += force->calculate(*this);

	return total_force;
}

void PhysicsBody::updateAcceleration() {
	if (_mass > Constants::EPSILON)
		_acceleration = calculateTotalForce() / _mass;
	else {
		Logger::warning("Mass of body '" + _name + "' is zero or negative, cannot update acceleration.");
		_acceleration = Vector();
	}
}
