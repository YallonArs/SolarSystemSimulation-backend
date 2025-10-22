#include "CoordinateTransformer.h"
#include <iostream>

PhysicsBody::State CoordinateTransformer::keplerToCartesian(const KeplerCoords &kepler, double centralMass) {
	PhysicsBody::State state;

	// For hyperbola, a < 0
	double p = kepler.a * (1 - pow(kepler.e, 2));

	double cosLimit = -1.0 / kepler.e;
	double cosPhi = std::cos(kepler.phi);
	if (cosPhi < cosLimit)
		cosPhi = cosLimit; // avoid negative r for unphysical phi - only relevant for hyperbolic trajectories
	double r = p / (1 + kepler.e * cosPhi);

	double A = sqrt(Constants::GRAVITATIONAL_CONSTANT * centralMass / p);

	state.position = Vector::fromPolar({r, kepler.phi + kepler.omega}).point();
	state.velocity = Vector(kepler.e * sin(kepler.phi), 1 + kepler.e * cos(kepler.phi)).rotated(kepler.phi + kepler.omega) * A;

	return state;
}

// v0: velocity at periapsis
// q: periapsis distance
// r: starting distance
PhysicsBody::State CoordinateTransformer::vqToCartesian(const double v0, const double q, double r, double centralMass) {
	PhysicsBody::State state;

	double E_total = v0 * v0 / 2 - Constants::GRAVITATIONAL_CONSTANT * centralMass / q;

	// even for hyperbolic trajectories, a is defined as negative
	double a = -Constants::GRAVITATIONAL_CONSTANT * centralMass / (2 * E_total);
	double e = 1 - q / a;

	double phi;

	if (E_total >= 0) {
		// orbit is parabolic or hyperbolic
		phi = std::acos((a * (1 - e * e) / r - 1) / e);
	} else {
		// orbit is elliptical

		// overwriting r to apoapsis distance
		r = a * (1 + e);

		phi = Constants::PI;
	}
	
	KeplerCoords kepler(a, e, 0.0, phi);
	state = keplerToCartesian(kepler, centralMass);
	state.velocity = -state.velocity; // reverse velocity direction to match starting at apoapsis
	return state;
}
