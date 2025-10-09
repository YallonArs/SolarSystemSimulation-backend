#include "SolarSystem.h"

SolarSystem SolarSystem::loadFromConfig(const Config& config) {
	// SolarSystem solarSystem;

	// // Load bodies from config
	// auto bodiesConfig = config.get("bodies");
	// for (const auto& bodyConfig : bodiesConfig) {
	// 	CelestialBody body = CelestialBody::fromConfig(bodyConfig);
	// 	solarSystem.addBody(body);
	// }

	// // Set central body
	// std::string centralBodyName = config.get("central_body");
	// solarSystem.setCentralBody(centralBodyName);

	// return solarSystem;
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

// Analysis methods
double SolarSystem::getTotalSystemMass() const {
	double total = 0;

	for (auto body : _bodies)
		total += body->mass();

	return total;
}

// Simulation control
// void SolarSystem::update(double deltaTime) {
// 	auto all_bodies = getAllBodies();
// 	_physics_engine.calculateForces(all_bodies);
// }

Point SolarSystem::getSystemBarycenter() const {
	Point barycenter;
	double total_mass = getTotalSystemMass();

	for (auto body : _bodies)
		barycenter += body->position() * body->mass();

	return total_mass > Constants::EPSILON ? barycenter / total_mass : Point(0, 0);
}
