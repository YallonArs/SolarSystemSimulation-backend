#include "CoordinateTransformer.h"
#include <iostream>

PhysicsBody::State CoordinateTransformer::keplerToCartesian(const KeplerCoords &kepler, double centralMass) {
	PhysicsBody::State state;

	double p = kepler.a * (1 - pow(kepler.e, 2));
	double r = p / (1 + kepler.e * cos(kepler.phi));
	double A = sqrt(Constants::GRAVITATIONAL_CONSTANT * centralMass / p);

	state.position = Vector::fromPolar({r, kepler.phi + kepler.omega}).point();
	state.velocity = Vector(kepler.e * sin(kepler.phi), 1 + kepler.e * cos(kepler.phi)).rotated(kepler.phi + kepler.omega) * A;

	return state;
}
