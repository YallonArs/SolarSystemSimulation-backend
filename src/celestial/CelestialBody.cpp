#include "CelestialBody.h"

#include "math/MathUtils.h"

CelestialBody::CelestialBody(const std::string &name, double mass, const Point &position, const Vector &velocity)
	: PhysicsBody(name, mass, position, velocity), _parent_body(nullptr) {}

CelestialBody *CelestialBody::getParent() const {
	return _parent_body;
}

const std::vector<std::unique_ptr<CelestialBody>> &CelestialBody::getSatellites() const {
	return _satellites;
}

void CelestialBody::addSatellite(std::unique_ptr<CelestialBody> satellite) {
	satellite->_parent_body = this;
	_satellites.push_back(std::move(satellite));
	// TODO: translate parent coordinates and velocity to Cartesian
	// TODO: implement position and velocity adjustment based on parent's motion
}

void CelestialBody::setParent(CelestialBody *parent) {
	_parent_body = parent;
}

void CelestialBody::update(double deltaTime) {
	PhysicsBody::integrate(deltaTime);

	for (auto &satellite : _satellites)
		satellite->update(deltaTime);
}
