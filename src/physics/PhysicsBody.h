#pragma once

#include <memory>
#include <string>
#include <vector>

#include "geometry/Point.h"
#include "geometry/Vector.h"

#include "physics/Force.h"

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
	std::vector<Force*> _applied_forces;

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
	void setMass(double mass) { _mass = mass; }
	void setPosition(const Point &pos) { _state.position = pos; }
	void setVelocity(const Vector &vel) { _state.velocity = vel; }
	void setAcceleration(const Vector &acc) { _acceleration = acc; }

	// interaction
	void addForce(Force *force);
	void clearForces();
	Vector calculateTotalForce() const;
	void updateAcceleration();
};
