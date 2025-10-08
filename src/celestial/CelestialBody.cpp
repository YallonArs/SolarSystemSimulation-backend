#include "CelestialBody.h"

CelestialBody::CelestialBody(const CelestialProperties &other)
	: PhysicsBody(other.name, other.mass, other.state),
	  _parent_body(other.parent) {}

// TODO: test
void CelestialBody::addSatellite(CelestialBody& satellite) {
	satellite.setParent(this);
	satellite.shiftToParentReference();

	_satellites.push_back(&satellite);
}

void CelestialBody::shiftToParentReference() {
	if (!_parent_body) return;

	if (name() == _parent_body->name()) {
		setPosition(Point(0, 0));
		setVelocity(Vector(0, 0));
	} else {
		// TODO: may be plus?? v
		setPosition(position() - _parent_body->position());
		setVelocity(velocity() - _parent_body->velocity());
	}
}
