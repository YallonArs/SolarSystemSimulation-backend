#include "SolarSystem.h"

SolarSystem::~SolarSystem() {
	_bodies.clear();
	_body_registry.clear();
}

void SolarSystem::addBody(CelestialBody* body) {
	if (_body_registry.find(body->name()) != _body_registry.end())
		throw std::runtime_error("Body with name '" + body->name() + "' already exists in the system.");

	_body_registry[body->name()] = body;
	_bodies.push_back(body);
}

void SolarSystem::addComet(Comet* body) {
	_comets.push_back(body);
}

void SolarSystem::startComet(std::string name) {
	for (auto comet : _comets) {
		if (comet->name() == name) {
			addBody(static_cast<CelestialBody*>(comet));
			return;
		}
	}
}

CelestialBody* SolarSystem::findBody(const std::string &name) const {
	auto it = _body_registry.find(name);

	return (it != _body_registry.end()) ? it->second : nullptr;
}

CelestialBody* SolarSystem::getBodyByIndex(const uint16_t index) const {
	if (index >= _bodies.size())
		throw std::out_of_range("Index " + std::to_string(index) + " is out of range for bodies vector of size " + std::to_string(_bodies.size()) + ".");

	return _bodies[index];
}

CelestialBody* SolarSystem::operator[](const std::string &name) const {
	return findBody(name);
}

CelestialBody* SolarSystem::operator[](const uint16_t index) const {
	return getBodyByIndex(index);
}

void SolarSystem::setCentralBody(const std::string &name) {
	_central_body = findBody(name);
	
	for (auto body : _bodies){
		// If the body has an explicit parent name, resolve it. Otherwise
		// top-level bodies (no parentName) should be attached to central
		// body except the central body itself.
		if (body->getParentName() != "") {
			CelestialBody *p = findBody(body->getParentName());
			if (p) body->setParent(p);
		} else if (body != _central_body) {
			body->setParent(_central_body);
		}
	}
}

void SolarSystem::shiftToCentralBodyReference() {
	if (!_central_body) return;

	// Convert all bodies' states from parent-relative to global coordinates.
	// Start at central body (its position remains as-is) and recurse into
	// its satellites to set global positions/velocities.
	// The helper in CelestialBody will recurse children.
	for (auto body : _bodies) {
		if (body == _central_body) {
			body->setPosition(Point(0,0));
			body->setVelocity(Vector(0,0));
			// shift children of central body to global coordinates
			body->shiftChildrenToGlobal();
			break; // only need to start recursion once from central body
		}
	}
}
