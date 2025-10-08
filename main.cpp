#include <iostream>

#include "utils/Config.h"
#include "parser/Parser.h"
#include "celestial/SolarSystem.h"
#include "celestial/CelestialBody.h"
#include "celestial/CoordinateTransformer.h"
#include "simulation/Simulation.h"

int main() {
	// Parser parser;
	// Config config = parser.load();
	// config.print();

	SolarSystem solarSystem;
	Integrator integrator;

	CelestialProperties sun_props("Sun", 1.9e30);
	CelestialBody sun(sun_props);

	KeplerCoords earth_kepler(1.496e11, 0.0167, 0, 0);
	PhysicsBody::State earth_state = CoordinateTransformer::keplerToCartesian(earth_kepler, sun.mass());
	CelestialProperties earth_props("Earth", 5.972e24, earth_kepler, earth_state, &sun);

	CelestialBody earth(earth_props);

	// PhysicsBody sun("Sun", 1.9e30, Point(0, 0), Vector(0, 0));
	// PhysicsBody earth("Earth", 5.972e29, Point(1.496e11, 0), Vector(0, 20e3));
	// PhysicsBody moon("Moon", 7.348e22, Point(384.4e6 + 1.496e11, 0), Vector(0, (29.8e3)));

	solarSystem.addBody(sun);
	solarSystem.addBody(earth);

	solarSystem.setCentralBody("Sun");

	Simulator simulator(solarSystem, integrator);
	simulator.setTimeStep(1000); // 1000 second time step
	
	simulator.getSolarSystem().getBodies();

	// while time < one month do steps and print moon position to file
	simulator.start();
	// open file
	std::ofstream sun_file(".run/sun_position.txt");
	std::ofstream earth_file(".run/earth_position.txt");
	// std::ofstream moon_file(".run/moon_position.txt");
	for (int i = 0; i < 60 * 60 * 24 * 30. / 10; ++i) {
		simulator.step();
		sun_file << (int64_t)sun.position().x() << " " << (int64_t)sun.position().y() << std::endl;
		earth_file << (int64_t)earth.position().x() << " " << (int64_t)earth.position().y() << std::endl;
		// moon_file << (int64_t)moon.position().x() << " " << (int64_t)moon.position().y() << std::endl;
	}
	sun_file.close();
	// moon_file.close();
	earth_file.close();
}
