#include "physics/PhysicsBody.h"

PhysicsBody::PhysicsBody(double mass, const Point &position, const Vector &velocity)
	: _mass(mass), _position(position), _velocity(velocity), _acceleration{} {}

void PhysicsBody::addForce(std::unique_ptr<Force> force) {
	_applied_forces.push_back(std::move(force));
}

void PhysicsBody::clearForces() {
	_applied_forces.clear();
}

Vector PhysicsBody::calculateTotalForce() const {
	Vector total_force;
	for (const auto &force : _applied_forces)
		total_force += force->calculate(*this);
	
	return total_force;
}

void PhysicsBody::updateAcceleration() {
	if (_mass > Constants::EPSILON)
		_acceleration = calculateTotalForce() / _mass;
}

void PhysicsBody::integrate(double deltaTime) {
	updateAcceleration();
	_velocity += _acceleration * deltaTime;
	_position += _velocity * deltaTime;
}
