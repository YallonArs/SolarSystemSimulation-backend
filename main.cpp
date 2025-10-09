#include <iostream>

#include "celestial/CelestialBody.h"
#include "celestial/CoordinateTransformer.h"
#include "celestial/SolarSystem.h"
#include "parser/Parser.h"
#include "simulation/Simulation.h"
#include "utils/Config.h"

int main() {
	Parser parser;
	Config config = parser.load();

	SolarSystem solarSystem;
	Integrator integrator;

	std::string central_body_name = config.settings["system"]["central_body"].value_or("Sun");
	CelestialProperties central_body_props = *config.getBodyByName(central_body_name);
	CelestialBody central_body(central_body_props);

	for (CelestialProperties *body_props : config.bodies) {
		if (body_props->name != central_body_name) {
			PhysicsBody::State state = CoordinateTransformer::keplerToCartesian(body_props->kepler, central_body_props.mass);
			body_props->state = state;
		}
		CelestialBody *celestial_body = new CelestialBody(*body_props);
		solarSystem.addBody(celestial_body);
	}

	solarSystem.setCentralBody(central_body_name);

	/*
	// mercury
	KeplerCoords mercury_kepler(5.79e10, 0.2056, 0, 0);
	PhysicsBody::State mercury_state = CoordinateTransformer::keplerToCartesian(mercury_kepler, sun.mass());
	CelestialProperties mercury_props("Mercury", 3.285e23, mercury_kepler, mercury_state, &sun);
	CelestialBody mercury(mercury_props);

	// venus
	KeplerCoords venus_kepler(1.082e11, 0.0067, 0, 0);
	// KeplerCoords venus_kepler(1.082e11, 0.67, 45 * Constants::DEG_TO_RAD, 0);
	PhysicsBody::State venus_state = CoordinateTransformer::keplerToCartesian(venus_kepler, sun.mass());
	CelestialProperties venus_props("Venus", 4.867e24, venus_kepler, venus_state, &sun);
	CelestialBody venus(venus_props);

	// earth
	KeplerCoords earth_kepler(1.496e11, 0.0167, 0, 0);
	PhysicsBody::State earth_state = CoordinateTransformer::keplerToCartesian(earth_kepler, sun.mass());
	CelestialProperties earth_props("Earth", 5.972e24, earth_kepler, earth_state, &sun);
	CelestialBody earth(earth_props);

	// mars
	KeplerCoords mars_kepler(2.279e11, 0.0934, 0, 0);
	PhysicsBody::State mars_state = CoordinateTransformer::keplerToCartesian(mars_kepler, sun.mass());
	CelestialProperties mars_props("Mars", 6.39e23, mars_kepler, mars_state, &sun);
	CelestialBody mars(mars_props);

	// jupyter
	KeplerCoords jupyter_kepler(7.785e11, 0.0489, 0, 0);
	PhysicsBody::State jupyter_state = CoordinateTransformer::keplerToCartesian(jupyter_kepler, sun.mass());
	CelestialProperties jupyter_props("Jupyter", 1.898e27, jupyter_kepler, jupyter_state, &sun);
	CelestialBody jupyter(jupyter_props);

	// saturn
	KeplerCoords saturn_kepler(1.433e12, 0.0565, 0, 0);
	PhysicsBody::State saturn_state = CoordinateTransformer::keplerToCartesian(saturn_kepler, sun.mass());
	CelestialProperties saturn_props("Saturn", 5.683e26, saturn_kepler, saturn_state, &sun);
	CelestialBody saturn(saturn_props);

	// uranus
	KeplerCoords uranus_kepler(2.872e12, 0.0457, 0, 0);
	PhysicsBody::State uranus_state = CoordinateTransformer::keplerToCartesian(uranus_kepler, sun.mass());
	CelestialProperties uranus_props("Uranus", 8.681e25, uranus_kepler, uranus_state, &sun);
	CelestialBody uranus(uranus_props);

	// neptune
	KeplerCoords neptune_kepler(4.495e12, 0.0113, 0, 0);
	PhysicsBody::State neptune_state = CoordinateTransformer::keplerToCartesian(neptune_kepler, sun.mass());
	CelestialProperties neptune_props("Neptune", 1.024e26, neptune_kepler, neptune_state, &sun);
	CelestialBody neptune(neptune_props);

	solarSystem.addBody(sun);
	solarSystem.addBody(mercury);
	solarSystem.addBody(venus);
	solarSystem.addBody(earth);
	solarSystem.addBody(mars);
	solarSystem.addBody(jupyter);
	solarSystem.addBody(saturn);
	solarSystem.addBody(uranus);
	solarSystem.addBody(neptune);

	solarSystem.setCentralBody("Sun");
	*/

	Simulator simulator(solarSystem, integrator);
	simulator.setTimeStep(100); // 100 second time step

	// while time < one month do steps and print moon position to file
	simulator.start();
	// open file
	std::ofstream sun_file(".run/sun_position.txt");
	std::ofstream earth_file(".run/earth_position.txt");
	std::ofstream venus_file(".run/venus_position.txt");

	// // benchmark loop
	// auto start = std::chrono::high_resolution_clock::now();
	// for (int i = 0; i < 1e7; ++i)
	// 	simulator.step();
	// auto end = std::chrono::high_resolution_clock::now();
	// std::chrono::duration<double> elapsed = end - start;
	// std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
	// std::cout << "Steps per second: " << 1e7 / elapsed.count() << std::endl;
	// std::cout << "Ms per tick: " << elapsed.count() / 1e7 * 1000 << std::endl;

	// auto bodies = solarSystem.getBodies();
	// for (const auto body : bodies) {
	// 	std::cout << body->name() << " " << body->mass() << " " << body->position().x() << " " << body->position().y() << std::endl;
	// }

	for (int i = 0; i < 60 * 60 * 24 * 30. / 5; ++i) {
		simulator.step();
		// auto sun = *solarSystem.findBody("Sun");
		// std::cout << sun.mass();
		// std::cin.get();

		sun_file << (int64_t)solarSystem.findBody("Sun")->position().x() << " " << (int64_t)solarSystem.findBody("Sun")->position().y() << std::endl;
		earth_file << (int64_t)solarSystem.findBody("Earth")->position().x() << " " << (int64_t)solarSystem.findBody("Earth")->position().y() << std::endl;
		venus_file << (int64_t)solarSystem.findBody("Venus")->position().x() << " " << (int64_t)solarSystem.findBody("Venus")->position().y() << std::endl;
	}
	sun_file.close();
	venus_file.close();
	earth_file.close();
}
