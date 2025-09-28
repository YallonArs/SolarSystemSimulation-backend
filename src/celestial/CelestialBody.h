#pragma once

#include <vector>
#include <string>

#include "physics/PhysicsBody.h"

// implements satellite and parent body relationships
class CelestialBody : public PhysicsBody {
protected:
	std::vector<std::unique_ptr<CelestialBody>> _satellites;
	CelestialBody *_parent_body;

public:
	CelestialBody(const std::string &name, double mass, const Point &position, const Vector &velocity = Vector());

	// getters
	CelestialBody *getParent() const;
	const std::vector<std::unique_ptr<CelestialBody>> &getSatellites() const;

	// hierarchy management
	void addSatellite(std::unique_ptr<CelestialBody> satellite);
	void setParent(CelestialBody *parent);
	void update(double deltaTime);
};
