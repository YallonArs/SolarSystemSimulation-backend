#include <iostream>

#include "celestial/CelestialBody.h"
#include "celestial/CoordinateTransformer.h"
#include "celestial/SolarSystem.h"
#include "parser/Parser.h"
#include "simulation/Simulation.h"
#include "utils/Config.h"
#include "utils/string_utils.h"

int main() {
	Parser parser;
	Config config = parser.load();

	SolarSystem solarSystem;
	Integrator integrator;

	// init Sun
	std::string central_body_name = config.settings["system"]["central_body"].value_or("Sun");
	CelestialProperties central_body_props = *config.getBodyByName(central_body_name);
	CelestialBody central_body(central_body_props);

	std::vector<CelestialBody*> bodies_all;
	for (auto *body_props : config.bodies) {
		CelestialBody* body = new CelestialBody(*body_props);

		for (auto *sat_props : body_props->satellites) {
			CelestialBody *satellite = new CelestialBody(*sat_props);
			body->addSatellite(satellite);			
			bodies_all.emplace_back(satellite);
		}

		bodies_all.emplace_back(body);
	}

	// Set states for all bodies except central body (Sun)
	for (auto *body : bodies_all) {
		if (body->name() == central_body_name) continue;
		
		double parent_mass = central_body_props.mass;
		if (!body->getParentName().empty()) {
			CelestialProperties *parent_props = config.getBodyByName(body->getParentName());
			if (parent_props)
				parent_mass = parent_props->mass;
		}
		body->setStateFromKepler(body->getKepler(), parent_mass);
	}

	for (auto *body : bodies_all){
		body->shiftToParentReference();
		solarSystem.addBody(body);
	}

	solarSystem.setCentralBody(central_body_name);
	solarSystem.shiftToCentralBodyReference();

	Simulator simulator(solarSystem, integrator);
	simulator.setTimeStep(100); // 100 second time step

	// // benchmark loop
	// auto start = std::chrono::high_resolution_clock::now();
	// for (int i = 0; i < 1e6; ++i)
	// 	simulator.step();
	// auto end = std::chrono::high_resolution_clock::now();
	// std::chrono::duration<double> elapsed = end - start;
	// std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
	// std::cout << "Steps per second: " << 1e6 / elapsed.count() << std::endl;
	// std::cout << "Ms per tick: " << elapsed.count() / 1e6 * 1000 << std::endl;
	
	std::vector<std::ofstream> files;
	for (const auto &body : solarSystem.getBodies()) {
		std::string filename = ".run/" + str_tolower(body->name()) + "_position.txt";
		files.emplace_back(filename);
	}
	// while time < one month do steps and print moon position to files
	for (int i = 0; i < 60 * 60 * 24 * 30. / 100; ++i) {
		simulator.step();
		
		for (size_t j = 0; j < solarSystem.getBodies().size(); ++j) {
			CelestialBody *body = solarSystem.getBodies()[j];
			files[j] << (int64_t)body->position().x() << " " << (int64_t)body->position().y() << std::endl;
		}
	}

	for (auto &file : files)
		file.close();
}
