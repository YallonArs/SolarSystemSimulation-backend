#pragma once

#include <string>
#include <vector>
#include <map>

#include "CelestialProperties.h"
#include "physics/PhysicsBody.h"

class CelestialBody : public PhysicsBody {
protected:
	std::vector<CelestialBody*> _satellites;
	CelestialBody *_parent_body;
	std::string _parent_body_name;
	KeplerCoords _kepler;
	std::map<std::string, double> _custom_params;

public:
	CelestialBody(const CelestialProperties &other);

	// getters
	CelestialBody *getParent() const { return _parent_body; }
	std::string getParentName() const { return _parent_body_name; }
	KeplerCoords getKepler() const { return _kepler; }
	const std::vector<CelestialBody*> &getSatellites() const { return _satellites; }
	const std::map<std::string, double> &getCustomParams() const { return _custom_params; }

	// setters
	void setParent(CelestialBody *parent) { _parent_body = parent; }

	// hierarchy management
	void addSatellite(CelestialBody *satellite);
	void shiftToParentReference();

	// Shift all children recursively from parent-relative to global coords.
	void shiftChildrenToGlobal();

	// Set state from Keplerian elements and shift to global coordinates if parent is set
	void setStateFromKepler(const KeplerCoords& kepler, double parent_mass);

	bool operator==(const CelestialBody &other) const { return name() == other.name(); }
};
