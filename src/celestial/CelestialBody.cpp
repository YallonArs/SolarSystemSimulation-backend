#include "CelestialBody.h"
#include "CoordinateTransformer.h"

CelestialBody::CelestialBody(const CelestialProperties &props)
	: PhysicsBody(props.name, props.mass, props.state),
	  _parent_body_name(props.parentName), _parent_body(nullptr), _kepler(props.kepler) {}

void CelestialBody::addSatellite(CelestialBody *satellite) {
	satellite->setParent(this);
	satellite->shiftToParentReference();
	_satellites.push_back(satellite);
}

// Shifts this body's position/velocity from parent-relative to global coordinates
void CelestialBody::shiftToParentReference() {
	if (!_parent_body) return;
	setPosition(position() + _parent_body->position());
	setVelocity(velocity() + _parent_body->velocity());
}

// sets this body's state from Keplerian elements, then shifts to global coordinates if parent is set
void CelestialBody::setStateFromKepler(const KeplerCoords &kepler, double parent_mass) {
	PhysicsBody::State state = CoordinateTransformer::keplerToCartesian(kepler, parent_mass);

	setState(state);
}

// recursively shift children to global coordinates (helper - not exposed)
void CelestialBody::shiftChildrenToGlobal() {
	for (auto child : _satellites)
		// convert this child's stored parent-relative state into global
		child->shiftToParentReference();
}
