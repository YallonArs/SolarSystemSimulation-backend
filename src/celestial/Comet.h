#pragma once

#include "celestial/CelestialBody.h"
#include "celestial/CelestialProperties.h"

struct CometProperties {
	std::string name;
	double mass, q, v, r_start;

	CometProperties(std::string name, double mass, double q, double v, double r_start)
		: name(name), mass(mass), q(q), v(v), r_start(r_start) {}
};

class Comet : public CelestialBody {
private:
	CometProperties _props;
	CelestialBody *_central_body;

public:
	Comet(const CometProperties &props, CelestialBody *central_body);

	CometProperties getProperties() const { return _props; }
};
