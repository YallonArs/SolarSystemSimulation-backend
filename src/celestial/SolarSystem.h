#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "physics/PhysicsEngine.h"
#include "celestial/CelestialBody.h"
#include "geometry/Point.h"
#include "utils/Config.h"

class SolarSystem {
private:
	std::vector<CelestialBody*> _bodies;
	PhysicsEngine _physics_engine;
	std::unordered_map<std::string, CelestialBody*> _body_registry;
	CelestialBody* _central_body = nullptr;

public:
	SolarSystem()
		: _physics_engine(PhysicsEngine())
		, _central_body(nullptr) {}

	~SolarSystem();

	void addBody(CelestialBody* body);
	CelestialBody* findBody(const std::string &name);

	CelestialBody* getCentralBody() const { return _central_body; }
	const std::vector<CelestialBody *> getBodies() const { return _bodies; }

	void setCentralBody(const std::string &name);
	void shiftToCentralBodyReference();

private:
	std::vector<CelestialBody*> getAllBodies() { return _bodies; }
};
