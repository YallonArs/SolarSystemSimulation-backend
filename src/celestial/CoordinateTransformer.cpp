#include "CoordinateTransformer.h"
#include <iostream>

PhysicsBody::State CoordinateTransformer::keplerToCartesian(const KeplerCoords &kepler, double centralMass) {
	// print kepler coords
	std::cout << "Kepler coords: a=" << kepler.a << " e=" << kepler.e << " omega=" << kepler.omega << " phi=" << kepler.phi << std::endl;
	// print mass
	std::cout << "Central mass: " << centralMass << std::endl;

	PhysicsBody::State state;

	double p = kepler.a * (1 - pow(kepler.e, 2));
	std::cout << "p=" << p << std::endl;

	double r = p / (1 + kepler.e * cos(kepler.phi));
	double A = sqrt(Constants::GRAVITATIONAL_CONSTANT * centralMass / p);

	// print r and A
	std::cout << "r=" << r << " A=" << A << std::endl;

	state.position = Vector::fromPolar({r, kepler.phi + kepler.omega}).point();
	state.velocity = Vector(kepler.e * sin(kepler.phi), 1 + kepler.e * cos(kepler.phi)).rotated(kepler.phi + kepler.omega) * A;

	// print state
	std::cout << "Cartesian coords: x=" << state.position.x() << " y=" << state.position.y()
			  << " vx=" << state.velocity.x() << " vy=" << state.velocity.y() << std::endl;
	// cin
	std::cin.get();

	return state;
}
