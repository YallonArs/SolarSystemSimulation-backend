#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "physics/PhysicsEngine.h"
#include "celestial/CelestialBody.h"
#include "geometry/Point.h"
#include "utils/Config.h"
#include "celestial/Comet.h"

class SolarSystem {
private:
	std::vector<CelestialBody*> _bodies;  // except comets!
	std::vector<Comet*> _comets;
	PhysicsEngine _physics_engine;
	std::unordered_map<std::string, CelestialBody*> _body_registry;
	CelestialBody* _central_body = nullptr;

public:
	SolarSystem()
		: _physics_engine(PhysicsEngine())
		, _central_body(nullptr) {}

	~SolarSystem();

	void addBody(CelestialBody* body);
	void addComet(Comet* body);
	void startComet(std::string name);
	CelestialBody* findBody(const std::string &name) const;
	CelestialBody* getBodyByIndex(const uint16_t index) const;
	CelestialBody* operator[](const std::string &name) const;
	CelestialBody* operator[](const uint16_t index) const;

	CelestialBody* getCentralBody() const { return _central_body; }
	const std::vector<CelestialBody*> getBodies() const { return _bodies; }
	const std::vector<Comet*> getComets() const { return _comets; }

	void setCentralBody(const std::string &name);
	void shiftToCentralBodyReference();

private:
	std::vector<CelestialBody*> getAllBodies() { return _bodies; }
};
