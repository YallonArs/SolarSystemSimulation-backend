#include <iostream>

#include "celestial/CelestialBody.h"
#include "celestial/CoordinateTransformer.h"
#include "celestial/SolarSystem.h"
#include "parser/Parser.h"
#include "simulation/Simulation.h"
#include "utils/Config.h"

std::string str_tolower(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(),
				   [](unsigned char c) { return std::tolower(c); } // correct
	);
	return s;
}

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

	Simulator simulator(solarSystem, integrator);
	simulator.setTimeStep(100); // 100 second time step

	// while time < one month do steps and print moon position to file
	simulator.start();

	std::vector<std::ofstream> files;
	for (const auto &body : solarSystem.getBodies()) {
		std::string filename = ".run/" + str_tolower(body->name()) + "_position.txt";
		files.emplace_back(filename);
	}

	// // benchmark loop
	// auto start = std::chrono::high_resolution_clock::now();
	// for (int i = 0; i < 1e7; ++i)
	// 	simulator.step();
	// auto end = std::chrono::high_resolution_clock::now();
	// std::chrono::duration<double> elapsed = end - start;
	// std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
	// std::cout << "Steps per second: " << 1e7 / elapsed.count() << std::endl;
	// std::cout << "Ms per tick: " << elapsed.count() / 1e7 * 1000 << std::endl;

	for (int i = 0; i < 60 * 60 * 24 * 30. / 10; ++i) {
		simulator.step();

		for (size_t j = 0; j < solarSystem.getBodies().size(); ++j) {
			CelestialBody *body = solarSystem.getBodies()[j];
			files[j] << (int64_t)body->position().x() << " " << (int64_t)body->position().y() << std::endl;
		}

	}

	for (auto &file : files)
		file.close();
}
