#pragma once

#include <string>
#include <vector>

#include "CelestialProperties.h"
#include "physics/PhysicsBody.h"

// TODO: implements satellite and parent body relationships
class CelestialBody : public PhysicsBody {
protected:
	std::vector<CelestialBody*> _satellites;
	CelestialBody *_parent_body;

public:
	CelestialBody(const CelestialProperties &other);

	// getters
	CelestialBody *getParent() const { return _parent_body; };
	const std::vector<CelestialBody*> &getSatellites() const { return _satellites; };

	// setters
	void setParent(CelestialBody *parent) { _parent_body = parent; };

	// hierarchy management
	void addSatellite(CelestialBody &satellite);
	void shiftToParentReference();

	bool operator==(const CelestialBody &other) const { return name() == other.name(); }
};
