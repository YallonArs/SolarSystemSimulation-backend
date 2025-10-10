#include "SolarSystem.h"

SolarSystem::~SolarSystem() {
	// for (auto body : _bodies)
	// 	delete body;
	
	_bodies.clear();
	_body_registry.clear();
	// delete _central_body;

	// double free error was here~
}

void SolarSystem::addBody(CelestialBody* body) {
	if (_body_registry.find(body->name()) != _body_registry.end())
		throw std::runtime_error("Body with name '" + body->name() + "' already exists in the system.");

	_body_registry[body->name()] = body;
	_bodies.push_back(body);
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
		if (body->getParent() != nullptr) continue;

		body->setParent(_central_body);
	}
}

void SolarSystem::shiftToCentralBodyReference() {
	if (!_central_body) return;

	for (auto body : _bodies) {
		body->shiftToParentReference();
	}
}
