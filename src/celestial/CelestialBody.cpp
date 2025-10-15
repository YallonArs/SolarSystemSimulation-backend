#include "CelestialBody.h"
#include "CoordinateTransformer.h"

CelestialBody::CelestialBody(const CelestialProperties &props)
	: PhysicsBody(props.name, props.mass, props.state),
	  _parent_body_name(props.parentName), _parent_body(nullptr), kepler(props.kepler) {}

// TODO: test
void CelestialBody::addSatellite(CelestialBody* satellite) {
	// keep satellite's relative state unchanged here; SolarSystem will
	// perform global shifting once the hierarchy is built.
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
// Sets this body's state from Keplerian elements, then shifts to global coordinates if parent is set
void CelestialBody::setStateFromKepler(const KeplerCoords& kepler, double parent_mass) {
	PhysicsBody::State state = CoordinateTransformer::keplerToCartesian(kepler, parent_mass);
	setPosition(state.position);
	setVelocity(state.velocity);
	if (_parent_body)
		shiftToParentReference();
}

// recursively shift children to global coordinates (helper - not exposed)
void CelestialBody::shiftChildrenToGlobal() {
	for (auto child : _satellites) {
		// convert this child's stored parent-relative state into global
		child->shiftToParentReference();
		// recurse into grandchildren
		child->shiftChildrenToGlobal();
	}
}
