#pragma once

#include <memory>
#include <vector>
#include <string>

#include "geometry/Point.h"
#include "geometry/Vector.h"

#include "physics/Force.h"

class PhysicsBody {
protected:
	std::string _name;
	double _mass;
	Point _position;
	Vector _velocity;
	Vector _acceleration;
	std::vector<std::unique_ptr<Force>> _applied_forces;

public:
	PhysicsBody(const std::string &name, double mass, const Point &position, const Vector &velocity = Vector());

	virtual ~PhysicsBody() = default;

	// getters
	const std::string &name() const { return _name; }
	double mass() const { return _mass; }
	const Point &position() const { return _position; }
	const Vector &velocity() const { return _velocity; }
	const Vector &acceleration() const { return _acceleration; }

	// setters
	void setMass(double mass) { _mass = mass; }
	void setPosition(const Point &pos) { _position = pos; }
	void setVelocity(const Vector &vel) { _velocity = vel; }
	void setAcceleration(const Vector &acc) { _acceleration = acc; }

	// interaction
	void addForce(std::unique_ptr<Force> force);
	void clearForces();
	Vector calculateTotalForce() const;
	void updateAcceleration();
	void integrate(double deltaTime);
};
