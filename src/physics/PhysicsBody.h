#pragma once

#include <memory>
#include <string>
#include <vector>

#include "geometry/Point.h"
#include "geometry/Vector.h"

#include "Force.h"

class PhysicsBody {
public:
	struct State {
		Point position;
		Vector velocity;
	};

protected:
	std::string _name;
	double _mass;
	State _state;
	Vector _acceleration;
	Vector _total_force;

public:
	PhysicsBody(const std::string &name, double mass, const State &state);

	virtual ~PhysicsBody() = default;

	// getters
	const std::string &name() const { return _name; }
	double mass() const { return _mass; }
	const Point &position() const { return _state.position; }
	const Vector &velocity() const { return _state.velocity; }
	const Vector &acceleration() const { return _acceleration; }

	// setters
	void setName(const std::string &name) { _name = name; }
	void setMass(double mass) { _mass = mass; }
	void setPosition(const Point &pos) { _state.position = pos; }
	void setVelocity(const Vector &vel) { _state.velocity = vel; }
	void setState(const State &state) { _state = state; }
	void setAcceleration(const Vector &acc) { _acceleration = acc; }

	// interaction
	void addForce(Force *force);
	void clearForces();
	void updateAcceleration();
};
