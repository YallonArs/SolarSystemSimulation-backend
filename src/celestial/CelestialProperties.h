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
	CelestialBody* parent = nullptr;

	CelestialProperties() : name(""), mass(0), kepler(), state(), parent(nullptr) {};

	CelestialProperties(const std::string &name, double mass, const KeplerCoords &kepler = KeplerCoords(), const PhysicsBody::State &state = PhysicsBody::State(), CelestialBody *parent = nullptr)
		: name(name), mass(mass), kepler(kepler), state(state), parent(parent) {};
};
