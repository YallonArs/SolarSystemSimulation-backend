#pragma once

#include "physics/PhysicsBody.h"

// forward-declaration to avoid circular include
class CelestialBody;

struct KeplerCoords {
	double a, e, omega, phi;

	KeplerCoords() : a(0), e(0), omega(0), phi(0) {};
	KeplerCoords(double a, double e, double omega, double phi) : a(a), e(e), omega(omega), phi(phi) {};
};

// it fully describes a celestial body
struct CelestialProperties {
	std::string name;
	double mass;
	KeplerCoords kepler;
	PhysicsBody::State state;
	std::string parentName = "";
	std::vector<CelestialProperties*> satellites;

	CelestialProperties() : name(""), mass(0), kepler(), state(), parentName(""), satellites() {};
	
	// deep copy constructor
	CelestialProperties(const CelestialProperties& other)
		: name(other.name), mass(other.mass), kepler(other.kepler), state(other.state), parentName(other.parentName)
	{
		for (const auto* sat : other.satellites) {
			if (sat)
				satellites.push_back(new CelestialProperties(*sat));
			else
				satellites.push_back(nullptr);
		}
	}

	CelestialProperties(const std::string &name, double mass, const KeplerCoords &kepler = KeplerCoords(), const PhysicsBody::State &state = PhysicsBody::State(), const std::string &parentName = "", std::vector<CelestialProperties*> satellites = std::vector<CelestialProperties*>())
		: name(name), mass(mass), kepler(kepler), state(state), parentName(parentName), satellites(satellites) {};

	void convertAU() {
		kepler.a *= Constants::ASTRONOMICAL_UNIT;
	}
};
