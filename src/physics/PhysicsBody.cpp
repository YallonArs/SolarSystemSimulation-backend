#include "PhysicsBody.h"
#include "utils/Logger.h"

PhysicsBody::PhysicsBody(const std::string &name, double mass, const State &state) 
	: _name(name), _mass(mass), _state(state) {}

void PhysicsBody::addForce(Force *force) {
	_total_force += force->calculate(*this);
}

void PhysicsBody::clearForces() {
	_total_force = Vector(0, 0);
}

void PhysicsBody::updateAcceleration() {
	if (_mass > Constants::EPSILON)
		_acceleration = _total_force / _mass;
	else {
		Logger::warning("Mass of body '" + _name + "' is zero or negative, cannot update acceleration.");
		_acceleration = Vector();
	}
}
