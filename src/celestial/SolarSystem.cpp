#include "SolarSystem.h"

SolarSystem::~SolarSystem() {
	for (auto body : _bodies) {
		delete body;
	}
	_bodies.clear();
	_body_registry.clear();
	delete _central_body;
}

void SolarSystem::addBody(CelestialBody* body) {
	if (_body_registry.find(body->name()) != _body_registry.end())
		throw std::runtime_error("Body with name '" + body->name() + "' already exists in the system.");

	_body_registry[body->name()] = body;
	_bodies.push_back(body);
}

#include <iostream>

CelestialBody* SolarSystem::findBody(const std::string &name) {
	auto it = _body_registry.find(name);

	// std::cout << "Finding body: " << name << " - " << (it != _body_registry.end() ? "Found" : "Not Found") << std::endl;
	// Print body details if found
	// std::cout << it->second->mass() << std::endl;

	return (it != _body_registry.end()) ? it->second : nullptr;
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
